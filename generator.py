#! /usr/bin/env python2

import sys
import os
import glob
import threading
import traceback
import subprocess
import argparse

def PrepareCommandLineArguments(argv):
    parser = argparse.ArgumentParser(description = 'Generate problem data and verify solutions.')
    parser.add_argument('-p', '--problem', required = True, type = str, dest = 'problem',
                        help = '''The problem sources folder, including solutions, 
                        generator, verifier and checker.''')
    parser.add_argument('--cpp', type = str, default = 'g++',
                        help = 'The C++ compiler command.')
    parser.add_argument('--cpp_flags', type = str,
                        default = '-O2 -Wall -std=gnu++0x -DONLINE_JUDGE -I. -Itestlib',
                        help = "The C++ compiler compiling extra flag.")
    parser.add_argument('-b', '--begin', type = int, default = 1, dest = 'begin_test_case',
                        help = 'The first test case number.')
    parser.add_argument('-e', '--end', type = int, default = 10, dest = 'end_test_case',
                        help = 'The last test case number.')
    parser.add_argument('--clean', action = 'store_true', dest = 'is_clean_mode',
                        help = 'Cleans the problem data if this flag added.')
    parser.add_argument('-t', '--timeout', type = int, dest = 'timeout', default = 2,
                        help = 'The time limit of the problem, unit measured by seconds.')

    return parser.parse_args()


def CheckProblemFolderStructure(problem_folder):
    generator_file = os.path.join(problem_folder, 'generator.cc')
    solver_file = os.path.join(problem_folder, 'solver.cc')
    verifier_file = os.path.join(problem_folder, 'verifier.cc')
    checker_file = os.path.join(problem_folder, 'checker.cc')
    if not os.path.exists(generator_file) or not os.path.isfile(generator_file):
        print 'Generator file not found.'
        sys.exit(1)
    if not os.path.exists(solver_file) or not os.path.isfile(solver_file):
        print 'Solver file not found.'
        sys.exit(1)
    if not os.path.exists(verifier_file) or not os.path.isfile(verifier_file):
        print 'Verifier file not found.'
        sys.exit(1)
    if not os.path.exists(checker_file) or not os.path.isfile(checker_file):
        print 'Checker file not found.'
        sys.exit(1)

    data_folder = os.path.join(problem_folder, "data")
    if not os.path.exists(data_folder) or not os.path.isdir(data_folder):
        try:
            os.makedirs(data_folder)
        except:
            print 'Creates data folder', data_folder, 'failed.'
            sys.exit(1)

    solutions_folder = os.path.join(problem_folder, 'srcs')
    solutions = []
    if os.path.exists(solutions_folder) and os.path.isdir(solutions_folder):
        for root, dirs, files in os.walk(solutions_folder):
            for file_name in files:
                if file_name.endswith('.cc'):
                    solutions.append(os.path.join(solutions_folder, file_name))
    return generator_file, solver_file, verifier_file, checker_file, data_folder, solutions


class Timer(threading.Thread):
    def __init__(self, command_line_arguments, stdin, stdout, stderr):
        threading.Thread.__init__(self)
        if stdin:
            self.stdin = open(stdin, 'r')
        else:
            f = open(os.path.join('.', 'threading.in'), 'w')
            f.write(' ')
            f.close()
            self.stdin = open(os.path.join('.', 'threading.in'), 'r')
        self.stdout = open(stdout, 'w') if stdout else open(os.path.join('.', 'threading.out'), 'w')
        self.stderr = open(stderr, 'w') if stderr else open(os.path.join('.', 'threading.err'), 'w')
        self.exit_code = 0xFF
        self.killed = False
        self.information = 'Not run yet.'
        self.process = subprocess.Popen(command_line_arguments,
                                        stdin = self.stdin,
                                        stdout = self.stdout,
                                        stderr = self.stderr,
                                        env = None)

    def run(self):
        try:
            self.process.communicate(self.stdin)
            self.exit_code = self.process.returncode
            self.information = 'process running completed.'
        except:
            if not self.killed:
                self.exit_code = -1
                self.information = '''The process was invoked with Runtime Error
                or Output Limit Exceeded.'''
        finally:
            if self.stdin:
                self.stdin.close()
            if self.stdout:
                self.stdout.close()
            if self.stderr:
                self.stderr.close()


def RunInSandBox(command_line_arguments, stdin = None, stdout = None, stderr = None, timeout = 300):
    timer = Timer(command_line_arguments, stdin, stdout, stderr)
    timer.start()
    timer.join(timeout)
    if timer.isAlive():
        timer.process.terminate()
        timer.join()
        timer.killed = True
        timer.information = 'The process time out with %.6f seconds.' % (timeout)
        timer.exit_code = 0x8F
    return timer.exit_code, timer.information, stdout, stderr


def Compile(cpp, cpp_flags, source):
    binary_file = source + '.bin'
    stdout_file = source + '.compile.out'
    stderr_file = source + '.compile.err'
    command_line_arguments = [ cpp, source ]
    for cpp_flag in cpp_flags.split(' '):
        command_line_arguments.append(cpp_flag)
    command_line_arguments.append('-o')
    command_line_arguments.append(binary_file)
    exit_code, information, stdout, stderr = RunInSandBox(command_line_arguments, 
                                                          stdout = stdout_file, 
                                                          stderr = stderr_file)
    if exit_code:
        print 'Compiler exited with exit code %d' % (exit_code)
        print 'Compiler process information: %s' % (information)
        print 'Compiler stderr:'
        print '==========================='
        for line in open(stderr, 'r'):
            print line[ : -1]
        sys.exit(1)
    return binary_file


def FileDiff(output_data_file, user_data_file):
    return RunInSandBox(['diff', output_data_file, user_data_file])[0] # exit_code


if __name__ == "__main__":
    args = PrepareCommandLineArguments(sys.argv[1 : ])

    if args.is_clean_mode:
        for pattern in ['*.bin', '*.in', '*.out', '*.err',
                      '%s/*.bin' % (args.problem),
                      '%s/*.compile.*' % (args.problem),
                      '%s/srcs/*.compile.*' % (args.problem),
                      '%s/srcs/*.bin' % (args.problem)]:
            for file_name in glob.glob(pattern):
                os.remove(file_name)
        sys.exit(0)

    generator_file, solver_file, \
    verifier_file, checker_file, \
    data_folder, solutions = CheckProblemFolderStructure(args.problem)
    solution_binaries = []

    print 'Compile components...'
    generator_binary = Compile(args.cpp, args.cpp_flags, generator_file)
    solver_binary = Compile(args.cpp, args.cpp_flags, solver_file)
    verifier_binary = Compile(args.cpp, args.cpp_flags, verifier_file)
    checker_binary = Compile(args.cpp, args.cpp_flags, checker_file)
    for solution in solutions:
        solution_binaries.append(Compile(args.cpp, args.cpp_flags, solution))
    print 'Completed.'

    for case in xrange(args.begin_test_case, args.end_test_case + 1):
        print 'Generating case #%04d...' % (case)
        input_data_file = os.path.join(data_folder, '%04d.in' % (case))
        output_data_file = os.path.join(data_folder, '%04d.out' % (case))
        user_data_file = os.path.join('.', '%04d.out' % (case))
        try:
            # generate data
            assert not RunInSandBox([generator_binary, '--case=%d' % (case)],
                                    stdout = input_data_file)[0] # exit_code
            # verifier input data
            assert not RunInSandBox([verifier_binary],
                                    stdin = input_data_file)[0]
            # use solver to generate output data
            assert not RunInSandBox([solver_binary],
                                    stdin = input_data_file,
                                    stdout = output_data_file,
                                    timeout = args.timeout)[0]
            # check solutions
            for solution_binary in solution_binaries:
                if solution_binary.endswith('ac.cc.bin'):
                    assert not RunInSandBox([solution_binary],
                                            stdin = input_data_file,
                                            stdout = user_data_file,
                                            timeout = args.timeout)[0]
                    assert not FileDiff(output_data_file, user_data_file)
                elif solution_binary.endswith('wa.cc.bin'):
                    assert not RunInSandBox([solution_binary],
                                            stdin = input_data_file,
                                            stdout = user_data_file,
                                            timeout = args.timeout)[0]
                    assert FileDiff(output_data_file, user_data_file)
                elif solution_binary.endswith('tle.cc.bin'):
                    assert RunInSandBox([solution_binary],
                                        stdin = input_data_file,
                                        stdout = user_data_file,
                                        timeout = args.timeout)[0] == 0x8F
        except:
            # retry
            traceback.print_exc(file = sys.stderr)
            sys.exit(1)

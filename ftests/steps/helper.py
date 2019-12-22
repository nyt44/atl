from multiprocessing import Process
from asserts import assert_equal

def start_and_register_process(function, function_args, process_name, context):
    proc = Process(target=function, args=function_args, name=process_name)
    proc.start()
    context.processes.append(proc)

def check_if_log_contain_expected_result(log_name, expected_result):
    with open(log_name, 'r') as log:
        actual_result = log.read()
    assert_equal(actual_result, expected_result)

def join_all_processes(context):
    for proc in context.processes:
        proc.join()

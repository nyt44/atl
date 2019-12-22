from behave import *
from multiprocessing import Process
import py_atl
import helper

client_result_log = 'client_result.log'

def server():
    exp_server = py_atl.exp_calc_server(1,2,2)
    exp_server.run()

def client(base, exp):
    exp_client = py_atl.exp_calc_client(1,2,2)
    result = exp_client.calculate(base, exp)
    with open(client_result_log, 'w') as client_result:
        client_result.write(str(result))

@given('Exponentiation server is running')
def step_impl(context):
    helper.start_and_register_process(server, (), 'exp_calc_server', context)

@when('Exponentiation clients sends base {base:d} and exponent {exponent:d}')
def step_impl(context, base, exponent):
    helper.start_and_register_process(client, (base, exponent), 'exp_calc_client', context)

@then('Exponentiation client receives {expected_result}')
def step_impl(context, expected_result):
    helper.join_all_processes(context)
    helper.check_if_log_contain_expected_result(client_result_log, expected_result)

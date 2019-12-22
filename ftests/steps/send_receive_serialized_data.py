from behave import *
from multiprocessing import Process
import py_atl
from asserts import assert_equal
import helper

rec_result_log = 'receiver_result.log'

def receiver():
    client = py_atl.client(1,2,1)
    received_data = client.receive()
    with open(rec_result_log, 'w') as receiver_result:
        receiver_result.write(received_data)

def sender(data_to_send):
    client = py_atl.client(1,2,1)
    client.send(data_to_send)

@given('receiving process is waiting for data')
def step_impl(context):
    helper.start_and_register_process(receiver, (), 'atl_receiver', context)

@when('sending process sends {data}')
def step_impl(context, data):
    helper.start_and_register_process(sender, (data,), 'atl_sender', context)

@then('receiving process gets {expected_result}')
def step_impl(context, expected_result):
    helper.join_all_processes(context)
    helper.check_if_log_contain_expected_result(rec_result_log, expected_result)

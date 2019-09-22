from behave import *
from multiprocessing import Process
import py_atl
from asserts import assert_equal

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
    rec_proc = Process(target=receiver, name='atl_receiver')
    rec_proc.start()
    context.processes.append(rec_proc)

@when('sending process sends {data}')
def step_impl(context, data):
    send_proc = Process(target=sender, args=(data,), name='atl_sender')
    send_proc.start()
    context.processes.append(send_proc)

@then('receiving process gets {expected_result}')
def step_impl(context, expected_result):
    with open(rec_result_log, 'r') as receiver_result:
        received = receiver_result.read()
    assert_equal(received, expected_result)

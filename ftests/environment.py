from behave import *
import subprocess
import os
import shutil
import re
from subprocess import Popen

daemon_log = 'atl_daemon.log'
test_dir = 'tests'

def create_dir_if_not_exist(name):
    try:
        os.mkdir(name)
    except FileExistsError:
        pass


def before_scenario(context, scenario):
    context.processes = []

    with open(daemon_log, 'w') as log:
        Popen(['../out/atl_daemon/atl_daemon'], stdout=log, stderr=log)


def after_scenario(context, scenario):
    subprocess.run('../out/examples/daemon_terminator')

    for proc in context.processes:
        proc.join()

    create_dir_if_not_exist(test_dir)
    test_output_path = os.path.join(test_dir, scenario.name.replace(' ', '_').lower())
    create_dir_if_not_exist(test_output_path)

    all_files = os.listdir()
    log_files = [file for file in all_files if re.match(r'.*\.log', file)]
    for log in log_files:
        shutil.move(log, os.path.join(test_output_path, log))

    with open(os.path.join(test_output_path, daemon_log), 'r') as log:
        lines = log.readlines()
        found = False
        for line in lines:
            if "ATL Daemon closed normally" in line:
                found = True
        assert found



TEMPLATE = subdirs

SUBDIRS= arm_client tests 

CONFIG += ordered

tests.depends = arm_client

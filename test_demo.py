import unittest
from demo import *

class TestDemo(unittest.TestCase):
    def test_1_should_equal_1(self):
        self.assertEquals(1,1)
    
    def test_add_1and_1_should_equal_2(self):
        self.assertEquals(2,add(1,1))

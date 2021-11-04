import RPi.GPIO as GPIO
import time


#-------------------------setup-------------------------#
#alle GPIO-Pins mit speziellen Eigenschaften werden als
#gewöhnliche IO-Pins benutzt:
GPIO.setmode(GPIO.BOARD)

Check_button_pin = 3

Check_LSensor_pin = 29
Check_SMotor_pin = 31
CSensor_pin = 32
EMotor_pin = 33
ISensor_pin = 35
LED_pin = 36
LSensor_pin = 37
VMotor_pin = 38
SMotor_pin = 40         
#-----------------------end setup-----------------------#



#------------------------delays-------------------------#
VMotor_delay = int(0)
Check_SMotor_delay = int(0) 
EMotor_delay = int(0)
SMotor_delay = int(0) #unused, but implemented
#----------------------end delays-----------------------#



#--------------------static Variables-------------------#
LOW = GPIO.LOW
HIGH = GPIO.HIGH 
VMotor_cnt = int(0) 
Check_flag = bool(0) 
#------------------end static Variables-----------------#



#------------------------functions----------------------#
def Check_LSensor_stat(status = 0):
    pass

def Check_LSensor_meas():
    pass

def Check_button(): #ist der Taster
    GPIO.setup(Check_button_pin, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
    if GPIO.input(Check_button_pin) == LOW:
        return False
    else:
        return True

def Check_SMotor_stat(status = 0):
    time.sleep(Check_SMotor_delay)
    GPIO.setup(Check_SMotor_pin,GPIO.OUT)
    GPIO.output(Check_SMotor_pin,status) 

def CSensor_stat(status = 0):
    pass 

def CSensor_meas():
    pass 

def EMotor_stat(status = 0):
    pass

def ISensor_stat(status = 0):
    pass

def ISensor_meas():
    pass

def LED_stat(status = 0):
    GPIO.setup(LED_pin,GPIO.OUT)
    GPIO.output(LED_pin,GPIO.HIGH)

def LSensor_stat(status = 0):
    GPIO.setup(LSensor_pin,GPIO.IN)
    
    
    

def LSensor_meas():
    pass

def SMotor_stat(status = 0):
    time.sleep(SMotor_delay)
    GPIO.setup(SMotor_pin,GPIO.OUT)
    GPIO.output(SMotor_pin,status)

def VMotor_stat(status = 0):
    time.sleep(VMotor_delay)
    GPIO.setup(VMotor_pin,GPIO.OUT) 
    GPIO.output(VMotor_pin,status)
    
#----------------------end functions--------------------#
    

clean_Pins = GPIO.cleanup()



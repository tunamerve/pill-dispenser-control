import dispenser_functions as f
#Einschalten und aktive_Spender werden von der Schnittstelle zur Verfügung gestellt

switch_on = 1
active_disp = [0,5,1,0,0,3]
transport = [0,0,0,0,0,0]

if switch_on == 1:
    
    for i in range(6):
        temp = i
        
        if active_disp[i] != 0:
            cnt_pills = active_disp[i]
            transport[temp] = cnt_pills
            program_cnt = 0
            
            while cnt_pills != 0:
                f.LED_stat(1)
                f.LSensor_stat(1)
                f.SMotor_stat(1)
                
                while f.LSensor_meas != f.LOW:
                    if f.VMotor_cnt == 3:
                        print("ERROR! dispenser (active_disp[i]) ist leer oder Tablette verklemmt die Ausgabe.")
                        break #hier muss eine Taster-Bestätigung ergänzt werden 
                    else:
                        f.SMotor_stat(0)
                        f.VMotor_stat(1)
                        f.VMotor_stat(0)
                        f.SMotor_stat(1)
                        f.VMotor_cnt += 1                        
                f.VMotor_cnt = 0 #funktioniert das?  
                f.SMotor_stat(0)
                
                '''
                if f.LSensor_meas == f.LOW: #wenn die Messung des Lichtsensors deutlich nach unten schwankt
                    f.VMotor_cnt = 0 #funktioniert das?  
                    f.SMotor_stat(0)
                else:
                    while f.VMotor_cnt <= 3 and f.LSensor_meas != f.LOW: #hier ebenfalls verstellen, je nach Wiederholungsanzahl 
                        if f.VMotor_cnt == 3:#verstellbar (wie oft soll der VMotor vor Errorausgabe eingeschaltet werden?)
                             print("ERROR! dispenser (active_disp[i]) ist leer oder Tablette verklemmt die Ausgabe.")
                             break #hier muss entweder ein 2. break (um die for-loop zu beenden) oder ein Taster-Bestätigung zum Fortführen des Codes eingebaut werden
                        f.SMotor_stat(0)
                        f.VMotor_stat(1)
                        f.VMotor_stat(0)
                        f.SMotor_stat(1)
                        f.VMotor_cnt += 1
                        '''
                        
                if transport[0] == 0:
                    transport[temp] = 1
                    temp -= 1
                    transport[temp] = (cnt_pills-1)
                else:
                    f.Check_flag = 1
                    transport[0] -= 1
                    
                while program_cnt <= (i+active_disp[i]+1):
                    
                    f.EMotor_stat(1)
                    f.ISensor_stat(1) 
                    if f.ISensor_meas == f.LOW:
                        pass
                    f.EMotor_stat(0)
                 
                    cnt_pills -= 1
                
                    if f.Check_flag == 1:
                        f.Check_flag = 0
                        f.Check_LSensor_stat(1)
                        f.CSensor_stat(1)
                        if f.Check_LSensor_meas == f.LOW:#gleiche Frage wie oben, wird pausiert, bis die Bedingung erfüllt ist? Oder geht es direkt weiter?
                            pass
                        if f.CSensor_meas != True:
                            print("CAUTION! There is an incorrect pill in the checking unit. Please press the button and catch the pill!")
                            if f.Check_button == True:
                                pass   #später schauen ob statt "pass" etwas anderes geschrieben werden kann.
                        f.Check_SMotor_stat(1)
                        f.Check_LSensor_stat(0)
                        f.CSensor_stat(0)
        
                    if cnt_pills != 0:
                        program_cnt += 1
                        break 
                    elif transport == [0,0,0,0,0,0]:
                        program_cnt += 1
                        break 
                    else:
                        if transport[1] == 1:
                            f.Check_flag = 1
                            transport.append(0)
                            transport.remove(1)
                            cnt_pills += 1
                        else:
                            transport.append(0) 
                            transport.remove(0)
                            cnt_pills += 1
                            
                    program_cnt += 1
               
        f.LSensor_stat(0)
        f.LED_stat(0)
     
    f.clean_Pins
    print("Die Tabletten sind bereit zur Vergabe.")
#Ende 
 
 
    
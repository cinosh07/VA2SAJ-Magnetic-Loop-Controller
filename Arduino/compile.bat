del "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Arduino.arduino.avr.mega.hex"
del "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Arduino.arduino.avr.mega.elf"
"C:\Users\Carl\Google Drive\HAM Radio\mag loop\arduino-cli\arduino-cli.exe" compile -p COM12 --fqbn arduino:avr:mega "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Mag_Loop_Control_V3.ino"
copy "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Mag_Loop_Control_V3.ino.arduino.avr.mega.hex" "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Arduino.arduino.avr.mega.hex"
copy "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Mag_Loop_Control_V3.ino.arduino.avr.mega.elf" "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Arduino.arduino.avr.mega.elf"
del "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Mag_Loop_Control_V3.ino.arduino.avr.mega.hex"
del "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino\Mag_Loop_Control_V3.ino.arduino.avr.mega.elf"
"C:\Users\Carl\Google Drive\HAM Radio\mag loop\arduino-cli\arduino-cli.exe" upload -p COM12 --fqbn arduino:avr:mega "C:\Users\Carl\Documents\VA2SAJ-Magnetic-Loop-Controller\Arduino"

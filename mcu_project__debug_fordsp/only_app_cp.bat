@echo on
set current_path=%cd%

::del D:\E\code\mcu_project\source\Keil_project\app_out\App.bin
del %current_path%\source\Keil_project\app_out\App.bin

::copy D:\E\code\mcu_project\source\Keil_project\output\Project.bin D:\E\code\mcu_project\source\Keil_project\app_out\App.bin
copy %current_path%\source\Keil_project\output\Project.bin %current_path%\source\Keil_project\app_out\App.bin


d:
cmd

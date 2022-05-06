RT-Druid does not exist for arm9 thus we need to create conf.h by ourself

Usualy RT-Druid would generate the files in the fake_druid folder using conf.oil
 
This file does nothing but to check what app_0 did and check if the timer interrupt works.
This app will require addaptation if the internal working of the IRQhandler is changed!
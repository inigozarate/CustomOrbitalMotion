#!/bin/bash
echo -e "\e[1;32mPostprocessing has started\e[0m"
cmd.exe /c "D:\Usuarios\877575\Documents\batch_files\animation_overallview_T0.6.bat"
echo -e "\e[4;36mOverall rendering of the cylindrical tank is done\e[0m"
cmd.exe /c "D:\Usuarios\877575\Documents\batch_files\animation_x_direction_glyphs_T0.6.bat"
echo -e "\e[4;36mIsocontours are saved for later postprocessing\e[0m"
cmd.exe /c "D:\Usuarios\877575\Documents\batch_files\animation_y_direction_glyphs_T0.6.bat"
echo -e "\e[4;36mSlices of the y direction are saved\e[0m"

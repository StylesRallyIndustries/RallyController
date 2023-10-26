    Functions:
    4 x Buttons
    2 x Toggleable Profiles
    Bluetooth LE
    Bounce protection

    Notes for Android Keycodes:
    bleKeyboard.write(XX) is the ASCII Char in DEC format (A = 65, a = 97)
    In Locus or similar set the expected Keycode to the Constant Value / Android KeyEvent syntax
    KEYCODE_A = Constant Value: 29, KEYCODE_VOLUME_UP = Constant Value: 24
    For DMD2 you must follow the implementation guide below.
    Links:
    https://www.asciitable.com/asciifull.gif
    https://developer.android.com/reference/android/view/KeyEvent
    https://www.drivemodedashboard.com/controller-implementation-guide/
    https://docs.locusmap.app/doku.php?id=manual:user_guide:settings:control#use_hardware_controllers
    https://www.rallynavigator.com/rally-navigator-mobile-application

    Changelog:
    v1, 26/10/2023
    Moved code to github, 
    Fixed DMD2 integration. 
    
    v.09, 23/10/2023
    Added toggle mode for 2 x profiles,
    Figured out how to change name of device while powered,
    adc_power_off() for wifi power down has been depreciated, will look at other options,
    Removed wifi power down and cpu throttling as now 12v powered.

    v0.8, 17/09/2023
    Serial output bug related to throttled CPU identified,
      doesn't seem to impact functionality.

    v0.7, 28/08/2023
    Set CPU Throttle function (currently 80MHZ)
    Disabled WIFI module via ADC Power Off
    Fixed Button hold function
    Fixed Bonding / Pairing functions
    Formatted Serial Output

    v0.6, 27/08/2023
    Changed max bonded devices to 9
    Cleaned up code and fixed BT address reporting and bonding.
    Disabled NimBLE as it was causing start up errors, will come back to this later.
      02:07:19.708 -> ESP_ERROR_CHECK failed: esp_err_t 0x103 (ESP_ERR_INVALID_STATE) at 0x40092f30
      02:07:19.708 -> file: "C:\Users\snoopy\Documents\Arduino\libraries\NimBLE-Arduino\src\NimBLEDevice.cpp" line 879
      02:07:19.756 -> func: static void NimBLEDevice::init(const string&)
      02:07:19.756 -> expression: esp_bt_controller_init(&bt_cfg)
      02:07:19.756 ->
      02:07:19.756 -> abort() was called at PC 0x40092f33 on core 1

    v0.5, 14/08/2023
    Fully configured for DMD2 functions.
    DMD2 Beta required for 'DMD2 CTL xK' device names.

    v0.4, 13/08/2023
    Cleaned up code, added functions for button holding, only single
    repeating character so far.
    Tested multiple device names, appears that 'CICTRL' is the only
    name detected by DMD2.

    v0.3, 12/08/2023
    Added mapping for DMD2 and changed Device name to required value.
    Updated GPIO assignment.

    v0.2, 11/08/2023
    Modified GPIO assignment and removed all unnecessary code.

    v0.1, 05/08/2023
    Created new sketch and reorganised some functions and commands.

# AccountManager
Very lightweight steam account switcher, useful for quick switching alt accounts if you have more than 10 of them like i do

# Usage
1. Drop the exe into a folder, in this example ``x64\Release``
2. Create a new text file called ``accounts.kak``, make sure the extension is **.kak**
3. Paste in/Add your accounts in the format of ``Username``**:**``Password``
4. Launch the exe, and you should see the program saying it detected your accounts
5. Select the option ``Login`` in this instance, 1
6. Now select one of your accounts by selecting it by number next to it
7. The program will now kill the steam process and automatically login into your selected account

# Notice
Current version of the program takes a while to close the steam process, this can be fixed by replacing how the process is actually being found in the code
 ``Helpers\Helpers.cpp -> line: 25`` (small todo for me i guess)
 
If you want to change how the program recognizes account lists, change ``DEFAULT_ACCOUNT_FILE_NAME`` located in ``Helpers\Helpers.h -> line: 12``

The program requires Admin privledges due to the usage of ``OpenProcess``, ``TerminateProcess`` etc. (used for killing the steam process, i dont like using ``system()``)

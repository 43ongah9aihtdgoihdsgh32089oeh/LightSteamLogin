# AccountManager
Very lightweight steam account switcher, useful for quick switching alt accounts if you have more than 10 of them like i do

# Usage
1. Drop the exe into a folder, in this example ``x64\Release``
2. Create a new text file called ``accounts.kak``, make sure the extension is **.kak**
 ![explorer_j2mDnJ8AxS](https://github.com/43ongah9aihtdgoihdsgh32089oeh/LightSteamLogin/assets/138796100/3de78ed4-dec1-4488-81c9-062a20d9e09b)

4. Paste in/Add your accounts in the format of ``Username``**:**``Password``
 ![Code_to2ckzdtVb](https://github.com/43ongah9aihtdgoihdsgh32089oeh/LightSteamLogin/assets/138796100/bea1ec9a-3b6d-434c-8490-6f9379770f35)

6. Launch the exe, and you should see the program saying it detected your accounts
 ![AccountManager_Wt1gX2g7Fe](https://github.com/43ongah9aihtdgoihdsgh32089oeh/LightSteamLogin/assets/138796100/7cc49303-6ba4-4c1c-bce7-650c61ae7d09)

8. Select the option ``Login`` in this instance, 1
 ![AccountManager_WgC0l1kza2](https://github.com/43ongah9aihtdgoihdsgh32089oeh/LightSteamLogin/assets/138796100/61b1cf8c-16a4-47da-a85a-fdcde50fb4fc)

10. Now select one of your accounts by selecting it by number next to it (check picture above)
11. The program will now kill the steam process and automatically login into your selected account

# Notice
Current version of the program takes a while to close the steam process, this can be fixed by replacing how the process is actually being found in the code
 ``Helpers\Helpers.cpp -> line: 25`` (small todo for me i guess)
If you want to change how the program recognizes account lists, change ``DEFAULT_ACCOUNT_FILE_NAME`` located in ``Helpers\Helpers.h -> line: 12``

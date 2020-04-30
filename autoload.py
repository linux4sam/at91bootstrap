import os
import sys
import shutil
from javax.swing import JPanel, JLabel , JTextField, BoxLayout
from java.awt import BorderLayout
from shutil import copyfile

log.setShowOutput(False)
# log.info("Java version: " + System.getProperty("java.version"))
# log.info("Jython version: " + sys.version)
# log.info("Script path:" + os.path.dirname(os.path.abspath("__file__")))
# log.info("Autoload SYS_PATH:" + '\n'.join(sys.path))
for key in sys.modules.keys():
    if "mpconfig" in key:
        del sys.modules[key]
from scripts.mpconfig.mpconfig import MPConfig
from scripts.mpconfig import defconfig
from scripts.mpconfig import genconfig
from scripts import addpmecchead

def mplab_configure_Kconfig(confName):
    global app
    global project_dir

    if os.getcwd() != project_dir:
        os.chdir(project_dir)

    # log.info("mplab_configure_Kconfig: " + confName)
    dot_config_file = os.path.join(project_dir, confName + ".config")
    if not os.path.isfile(dot_config_file):
        # Create empty default.config file if it does not exist
        open(dot_config_file, 'a').close()

    kconfig_file = os.path.join(os.getcwd(), "Kconfig")

    # Set up GUI
    mpconfigPanel = JPanel()
    if os.path.isfile(kconfig_file):
        app = MPConfig(kconfig_file, dot_config_file, log)
        mpconfigPanel = app.getPane()

    rootPanel = JPanel()
    rootPanel.setLayout(BorderLayout())
    rootPanel.add(mpconfigPanel, BorderLayout.CENTER)

    return rootPanel


def save_mplab_configure_Kconfig(confName):
    global app
    global project_dir

    # log.info("save_mplab_configure_Kconfig: " + confName)
    try:
        dot_config_file = os.path.join(project_dir, confName + ".config")
        app.writeConfig(dot_config_file)

        if confName == active_config:
            if os.path.isdir(os.path.join(project_dir, "config", "at91bootstrap-config")):
                shutil.rmtree(os.path.join(project_dir, "config", "at91bootstrap-config"))
            os.makedirs(os.path.join(project_dir, "config", "at91bootstrap-config"))
            defconfig.main([dot_config_file])
            genconfig.main(["--sync-deps", os.path.join("config", "at91bootstrap-config"), "--header-path", os.path.join("config", "at91bootstrap-config", "autoconf.h")])
            shutil.copyfile(dot_config_file, os.path.join(project_dir, ".config"))
    except:
        pass


def onload(ide):
    # Load any stored settings
    global project_dir
    project_dir = ide.expandProjectMacros("${ProjectName}", "${ProjectDir}")

def on_project_build(e):
    global project_dir

    dot_config_path = os.path.join(project_dir, ".config")
    binaries_path = os.path.join(project_dir, "binaries")
    addpmecchead.pmecchead(dot_config_path, binaries_path)


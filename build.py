import os
from Source.Dependencies.Panshilar import buildutils

FOLDER_STRUCTURE = buildutils.getFolderStructure(os.path.dirname(os.path.abspath(__file__)))
MAIN_FILE = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.c'

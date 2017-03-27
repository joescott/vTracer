#ifndef DEF_H
#define DEF_H

#define PROGRAM_NAME            "vTrazer"
#define PROGRAM_VERSION         "0.1"
#define PROGRAM_YEAR_RELEASE    "2013"
#define PROGRAM_COMPANY         "Raccoon Systems"
#define PROGRAM_AUTOR           "Jorge Esteban Courett"
#define PROGRAM_LOGO            "<img src=\":/img/logoabout\">"

#define PROGRAM_ABOUT       PROGRAM_LOGO\
                            +tr("<center> %1 Version %2 </center>")\
                                .arg(PROGRAM_NAME)\
                                .arg(PROGRAM_VERSION)\
                            +tr("<p>This piece of junk is the best software ever written.</p>")\
                            +tr("<center>&copy; %1 - %2 - %3 </center>")\
                                .arg(PROGRAM_COMPANY)\
                                .arg(PROGRAM_YEAR_RELEASE)\
                                .arg(PROGRAM_AUTOR)

#define HELP_SUB_DIR    "doc"
#define HELP_FILE       "vTrazer_manual.pdf"

#define LANG_PATH               "lang"
#define SESSION_PATH            "session"

#define PLUGIN_MODEL_PATH       "plugins/models"
#define PLUGIN_MODEL_PREFIX     "lib"
#define PLUGIN_MODEL_POSFIX     ".so"

#define PLUGIN_ACTION_PATH       "plugins/actions"
#define PLUGIN_ACTION_PREFIX     "lib"
#define PLUGIN_ACTION_POSFIX     ".so"

#define CF_LANGUAGE    "LANGUAGE"
#define LANG_DEFINITION(x)   {\
    x["qs_es"] = "Español";\
    x["qs_en"] = "English";\
    }
/**
 * Configuration File
 */
#define CF_PATH            "conf.ini"
#define CF_APP_PATH        "Application/APP_PATH"
#define CF_APP_PATH_DF     "/bin/ls"
#define CF_APP_OPTIONS     "Application/APP_OPTIONS"
#define CF_APP_OPTIONS_DF  "-la"
#define CF_APP_PARSER      "Application/APP_PARSER"
#define CF_APP_PARSER_DF   "echoplugin"
#define CF_LOG_PATH        "log"

/**
 * Session File
 */
/** Parser */
#define PARSER_DFT_TYPE                 "parsertype"
/** Filters */
#define FILTER_DFT_ARRAY                "filters"
#define FILTER_CONDITION_DFT_ARRAY      "conditions"
#define FILTER_DFT_INDEX                "index"
#define FILTER_DFT_STATUS               "status"
#define FILTER_DFT_COLINDEX             "colindex"
#define FILTER_DFT_REGSTR               "regstr"
#define FILTER_DFT_CASESENCITIVE        "casesencitive"

/**
 *  Colors
 */

#define ERROR_COLOR     "RED"

/**
 *  APP
 */
#define APP_OPENFILE_LINES     1000
#define APP_OPENFILE_INTERVAL  200  //ms


#endif // DEF_H

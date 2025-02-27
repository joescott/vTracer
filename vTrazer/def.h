#ifndef DEF_H
#define DEF_H

#define PROGRAM_NAME            "vTrazer"
#define PROGRAM_VERSION         "0.2"
#define PROGRAM_YEAR_RELEASE    "2017"
#define PROGRAM_COMPANY         "Vortex"
#define PROGRAM_AUTOR           "JEC"
#define PROGRAM_LOGO            "<img src=\":/img/logoabout\">"

#define PROGRAM_ABOUT       PROGRAM_LOGO\
                            +tr("<center> %1 Version %2 </center>")\
                                .arg(PROGRAM_NAME)\
                                .arg(PROGRAM_VERSION)\
                            +tr("<p>RKH tracer log analyzer.</p>")\
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
#define CF_SESSION_FILE 				"SESSION_FILE"
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
#define FILTER_DFT_TYPE        			"type"
/** Watchs */
#define WATCH_DFT_ARRAY                 "watches"
#define WATCH_CONDITION_DFT_ARRAY       "conditions"
#define WATCH_DFT_INDEX                 "index"
#define WATCH_DFT_STATUS                "status"
#define WATCH_DFT_COLINDEX              "colindex"
#define WATCH_DFT_REGSTR                "regstr"
#define WATCH_DFT_CASESENCITIVE         "casesencitive"
#define WATCH_DFT_TYPE        	 	    "type"

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

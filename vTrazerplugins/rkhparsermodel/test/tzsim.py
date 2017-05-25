#!/usr/bin/env python3

import sys
import time
import re
import signal
import argparse
import os
import random

##
# Classes 
##

class pkg(object):
    """ Package Class """

    FORMAT          = "%11d| [%3d] | %3s | %-11s : %s"
    FORMAT_OPT      = "%39s| %-11s = %s\n"
    PARSE           = r'\s+(\d*)\|.*\[\s+(\d*)\]\s+\|\s+(.*)\s+\|\s+(.*)\s+:\s+(.*)'

    OBJ_CONF        = [{'type':'FWK','obj':'TCFG'}]
    PARSE_CONF      = r'\s+\|\s+(.*)\s+'
    PARSE_END       = r'^\s*$'  
    PARSE_CONF_OPT  = r'(.*)=(.*)'  
    FORMAT_ARGS     = "%s=%s"
    FORMAT_ARGS_SEP = ","

    SPLIT_ARGS      = r',' 
    PARSE_ARGS_OPT  = r'(.*)=(.*)'  

    def __init__(self, **entries):
        self.__dict__.update(entries)  

    def getDict(self):
        return self.__dict__

    def fmt(tick, seq, type, obj, args, opt):
        rtn = ""
        args_cnt = len(args)
        if args_cnt > 0:
            args_str=""
            for key, value in args.items():
                if key == 'positional':
                    args_str += pkg.FORMAT_ARGS_SEP.join(args['positional'])
                else:
                    args_str += pkg.FORMAT_ARGS % (key,value)

                args_cnt -= 1
                if args_cnt:
                    args_str += pkg.FORMAT_ARGS_SEP

            rtn = pkg.FORMAT % (tick,seq,type,obj,args_str)
        else:
            rtn = pkg.FORMAT % (tick,seq,type,obj,"")

        if len(opt):
            rtn += "\n"
            for key, value in opt.items():
                rtn += pkg.FORMAT_OPT % ("",key,value)

        return rtn

    def match(line):
        mobjs = re.match(pkg.PARSE, line,re.M|re.I)
        args = {} 
        for arg in mobjs.group(5).strip().split(pkg.SPLIT_ARGS):
            opt = re.match(pkg.PARSE_ARGS_OPT, arg,re.M|re.I)
            if opt != None:
                args[opt.group(1)] = opt.group(2).strip()
            else:
                if not 'positional' in args:
                    args['positional'] = [arg.strip()]
                else:
                    args['positional'].append(arg.strip())


        return pkg(**{'tick':mobjs.group(1).strip(),
                      'seq':mobjs.group(2).strip(), 
                      'type':mobjs.group(3).strip(), 
                      'obj':mobjs.group(4).strip(), 
                      'args':args,
                      'opt':{},
                      })

    def conf(line):
        mobjs = re.match(pkg.PARSE_CONF, line,re.M|re.I)
        return mobjs.group(1).strip()

    def conf_opt(opt_str):
        mobjs = re.match(pkg.PARSE_CONF_OPT, opt_str,re.M|re.I)
        return {mobjs.group(1).strip():mobjs.group(2).strip()}

    def isEnd(line):
        mobjs = re.match(pkg.PARSE_END, line,re.M|re.I)
        return mobjs != None 

    def isConfObj(self):
        for obj in pkg.OBJ_CONF:
            if self.type == obj['type'] and self.obj == obj['obj']:
                return True
        return False

class DB(dict):
    """ DB Class """

    def __init__(self):
        self._dict = {}

    def add(self, pkg):
        self._dict[pkg.type+pkg.obj] = pkg 

    def get(self, type, obj):
        return self._dict[type+obj]

    def getValue(self, key):
        return self._dict[key]

    def items(self): 
        return self._dict.items()

##
# Main Script 
##

def signal_handler(signal, frame):
        print('Bye!')
        sys.exit(0)

def loop(tick, DB, random_loop=False):
    count = 0
    t0 = time.time()
    while( True ):
        for key, o in DB.items():
            t = (time.time() - t0) * 1000
            print(pkg.fmt(t, count,o.type, o.obj, o.args, o.opt))
            sys.stdout.flush() 
            count = count + 1
            time.sleep(tick)

def parse_log_file(filename):
    """ Parse Log file and pupulate DB object """
    db = DB()
    try:
        CONF_TOKEN = False
        for line in open(filename,'r'):
            if pkg.isEnd(line):
                CONF_TOKEN = False
                db.add(p)
                continue

            if not CONF_TOKEN:
                p = pkg.match(line)
            else:
                p.opt.update(pkg.conf_opt(pkg.conf(line)))

            #print(p.getDict())

            if not CONF_TOKEN and p.isConfObj():
                CONF_TOKEN = True
            else:
                db.add(p)

    except Exception as e:
        print("Processing error %s[%s]" % (filename,e.message))
    
    return db

def termSet():
    os.system("stty -echo") 



if __name__ == "__main__":
    """ Parser main function """ 

    signal.signal(signal.SIGINT, signal_handler)

    termSet()

    ap = argparse.ArgumentParser()
    ap.add_argument('-f','--filename', type=str,   required=True, help="Input file")
    ap.add_argument('-t','--ticktime', type=float, required=False, help="Tick time interval")
    args = ap.parse_args() 

    DB = parse_log_file(args.filename)
    #print(DB.get('FWK','TCFG').getDict())
    #print(DB.get('FWK','OBJ').getDict())
    #print(DB.get('FWK','EN').getDict())
    if args.ticktime:
        loop(args.ticktime, DB, random_loop=True)
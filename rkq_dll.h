#ifndef RKQ_DLL_H
#define RKQ_DLL_H

#include "MarkRkdll.h"
#include <QLibrary>
class rkq_dll
{
public:
    rkq_dll();


bool initSDK();


public:
    QLibrary* rmc1lib;
    RKLM_INITIAL                rklm_initial;
    RKLM_SETVISIBLE             rklm_setvisible;
    RKLM_CLOSE                  rklm_close;
    RKLM_SETDEVCFG              rklm_setdevcfg;
    RKLM_SETDEVCFG2             rklm_setdevcfg2;
    RKLM_MARK                   rklm_mark;
    RKLM_MARKENTITY             rklm_markentity;
    RKLM_ISMARKING              rklm_ismarking;
    RKLM_STOPMARK               rklm_stopmark;
    RKLM_MARKLINE               rklm_markline;
    RKLM_MARKPOINT              rklm_markpoint;
    RKLM_MARKPOINTBUF2          rklm_markpointbuf2;
    RKLM_REDLIGHTMARK           rklm_redlightmark;
    RKLM_REDLIGHTMARKCONTOUR    rklm_redlightmarkcontour;
    RKLM_REDLIGHTMARKBYENT      rklm_redlightmarkbyent;
    RKLM_LOADRKQFILE            rklm_loadrkqfile;
    RKLM_SAVEENTLIBTOFILE       rklm_saveentlibtofile;
    RKLM_GETPREVBITMAP          rklm_getprevbitmap;
    RKLM_GETPREVBITMAPBYNAME    rklm_getprevbitmapbyname;
    RKLM_GETENTSIZE             rklm_getentsize;
    RKLM_MOVEENT                rklm_moveent;
    RKLM_SCALEENT               rklm_scaleent;
    RKLM_MIRRORENT              rklm_mirrorent;
    RKLM_ROTATEENT              rklm_rotateent;
    RKLM_COPYENT                rklm_copyent;
    RKLM_GETENTITYCOUNT         rklm_getentitycount;
    RKLM_GETENTITYNAME          rklm_getentityname;
    RKLM_SETENTITYNAME          rklm_setentityname;
    RKLM_CHANGEENTNAME          rklm_changeentname;
    RKLM_CHANGETEXTBYNAME       rklm_changetextbyname;
    RKLM_GETTEXTBYNAME          rklm_gettextbyname;
    RKLM_TEXTRESETSN            rklm_textresetsn;
    RKLM_GROUPENT               rklm_groupent;
    RKLM_UNGROUPENT             rklm_ungroupent;
    RKLM_GROUPENT2              rklm_groupent2;
    RKLM_MOVEENTITYBEFORE       rklm_moveentitybefore;
    RKLM_MOVEENTITYAFTER        rklm_moveentityafter;
    RKLM_REVERSEALLENTORDER     rklm_reverseallentorder;
    RKLM_GETBITMAPENTPARAM      rklm_getbitmapentparam;
    RKLM_GETTEXTENTPARAM       rklm_gettextentparam;
    RKLM_SETTEXTENTPARAM       rklm_settextentparam;
    RKLM_DELETEENT              rklm_deleteent;
    RKLM_CLEARENTLIB            rklm_clearentlib;
    RKLM_ADDTEXTTOLIB           rklm_addtexttolib;
    RKLM_ADDCIRCLETEXTTOLIB     rklm_addcircletexttolib;
    RKLM_GETCIRCLETEXTPARAM     rklm_getcircletextparam;
    RKLM_SETCIRCLETEXTPARAM     rklm_setcircletextparam;
    RKLM_ADDFILETOLIB           rklm_addfiletolib;
    RKLM_ADDCURVETOLIB          rklm_addcurvetolib;
    RKLM_ADDCURVETOLIB2         rklm_addcurvetolib2;
    RKLM_ADDDELAYTOLIB          rklm_adddelaytolib;
    RKLM_ADDWRITEPORTTOLIB      rklm_adddwriteporttolib;
    RKLM_ADDBARCODETOLIB        rklm_addbarcodetolib;
    RKLM_GETBARCODEPARAM        rklm_getbarcodeparam;
    RKLM_SETBARCODEPARAM        rklm_setbarcodeparam;
    RKLM_READPORT               rklm_readport;
    RKLM_GETOUTPORT             rklm_getoutport;
    RKLM_WRITEPORT              rklm_writeport;
    RKLM_GETHATCHPARAM3         rklm_gethatchparam3;
    RKLM_SETHATCHPARAM3         rklm_sethatchparam3;
    RKLM_GETHATCHENTPARAM2      rklm_gethatchentparam2;
    RKLM_SETHATCHENTPARAM2      rklm_sethatchentparam2;
    RKLM_HATCHENT               rklm_hatchent;
    RKLM_UNHATCHENT             rklm_unhatchent;
    RKLM_GETFONTPARAM3          rklm_getfontparam3;
    RKLM_SETFONTPARAM3          rklm_setfontparam3;
    RKLM_GETFONTRECORDCOUNT     rklm_getfontrecordcount;
    RKLM_GETALLFONTRECORD       rklm_getallfontrecord;
    RKLM_GETPENPARAM            rklm_getpenparam;
    RKLM_SETPENPARAM            rklm_setpenparam;
    RKLM_GETPENPARAM2           rklm_getpenparam2;
    RKLM_SETPENPARAM2           rklm_setpenparam2;
    RKLM_GETPENPARAM4           rklm_getpenparam4;
    RKLM_SETPENPARAM4           rklm_setpenparam4;



    RKLM_AXISCORRECTORIGIN      rklm_axiscorrectorigin;
    RKLM_GETAXISCOOR            rklm_getaxiscoor;
    RKLM_AXISMOVETO             rklm_axismoveto;
    RKLM_ISAXISRUNNING          rklm_isaxisrunning;
    RKLM_SETDEVCFG3             rklm_setdevcfg3;
    RKLM_SETDEVCFG4             rklm_setdevcfg4;
    RKLM_PRMMMARK               rklm_prmmmark;
    RKLM_ORMMMARK               rklm_ormmmark;

    //RKLM_GETAXISCOORPULSE       rklm_getaxiscoorpulse;
    //RKLM_AXISMOVETOPULSE        rklm_axismovetopulse;
    RKLM_VISIONPOINTSINPUT      rklm_visionpointsinput;
    //RKLM_RESET                  rklm_reset;
};

#endif // RKQ_DLL_H

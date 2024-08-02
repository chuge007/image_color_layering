#include "rkq_dll.h"
#include <QLibrary>
#include <QDebug>
#include <QCoreApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
rkq_dll::rkq_dll()
{
    initSDK();
    if(rklm_initial){
        QByteArray path = QCoreApplication::applicationDirPath().toLocal8Bit(); // QString转化为QByteArray
        char* path_char = path.data();
        auto ret = rklm_initial(path_char,true, /*(HWND)winId()*/nullptr);
    }

    //rklm_reset(true,true);
}



bool rkq_dll::initSDK()
{
    rmc1lib = new QLibrary("kernellib8");
    if(!rmc1lib->load())
    {
        qDebug() <<"Can not find MarkRkdll.dll!";
        return false;
    }
    else
    {
        rklm_initial=(RKLM_INITIAL)rmc1lib->resolve("rklm_initial");
        if(rklm_initial==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_initial in MarkRkq.dll!";
        }

        rklm_setvisible=(RKLM_SETVISIBLE)rmc1lib->resolve("rklm_setvisible");
        if(rklm_setvisible==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setvisible in MarkRkq.dll!";
        }

        rklm_close=(RKLM_CLOSE)rmc1lib->resolve("rklm_close");
        if(rklm_close==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_close in MarkRkq.dll!";
        }

        rklm_setdevcfg=(RKLM_SETDEVCFG)rmc1lib->resolve("rklm_setdevcfg");
        if(rklm_setdevcfg==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setdevcfg in MarkRkq.dll!";
        }

        rklm_setdevcfg2=(RKLM_SETDEVCFG2)rmc1lib->resolve("rklm_setdevcfg2");
        if(rklm_setdevcfg2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setdevcfg2 in MarkRkq.dll!";
        }

        rklm_mark=(RKLM_MARK)rmc1lib->resolve("rklm_mark");
        if(rklm_mark==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_mark in MarkRkq.dll!";
        }

        rklm_markentity=(RKLM_MARKENTITY)rmc1lib->resolve("rklm_markentity");
        if(rklm_markentity==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_markentity in MarkRkq.dll!";
        }

        rklm_ismarking = (RKLM_ISMARKING)rmc1lib->resolve("rklm_ismarking");
        if (rklm_ismarking == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_ismarking in MarkRkq.dll!";
        }

        rklm_stopmark = (RKLM_STOPMARK)rmc1lib->resolve("rklm_stopmark");
        if (rklm_stopmark == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_stopmark in MarkRkq.dll!";
        }

        rklm_markline = (RKLM_MARKLINE)rmc1lib->resolve("rklm_markline");
        if (rklm_markline == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_markline in MarkRkq.dll!";
        }

        rklm_markpoint = (RKLM_MARKPOINT)rmc1lib->resolve("rklm_markpoint");
        if (rklm_markpoint == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_markpoint in MarkRkq.dll!";
        }

        rklm_markpointbuf2 = (RKLM_MARKPOINTBUF2)rmc1lib->resolve("rklm_markpointbuf2");
        if (rklm_markpointbuf2 == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_markpointbuf2 in MarkRkq.dll!";
        }

        rklm_redlightmark = (RKLM_REDLIGHTMARK)rmc1lib->resolve("rklm_redlightmark");
        if (rklm_redlightmark == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_redlightmark in MarkRkq.dll!";
        }

        rklm_redlightmarkcontour = (RKLM_REDLIGHTMARKCONTOUR)rmc1lib->resolve("rklm_redlightmarkcontour");
        if (rklm_redlightmarkcontour == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_redlightmarkcontour in MarkRkq.dll!";
        }

        rklm_redlightmarkbyent = (RKLM_REDLIGHTMARKBYENT)rmc1lib->resolve("rklm_redlightmarkbyent");
        if (rklm_redlightmarkbyent == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_redlightmarkbyent in MarkRkq.dll!";
        }

        rklm_loadrkqfile=(RKLM_LOADRKQFILE)rmc1lib->resolve("rklm_loadrkqfile");
        if(rklm_loadrkqfile==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_loadrkqfile in MarkRkq.dll!";
        }

        rklm_saveentlibtofile=(RKLM_SAVEENTLIBTOFILE)rmc1lib->resolve("rklm_saveentlibtofile");
        if(rklm_saveentlibtofile==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_saveentlibtofile in MarkRkq.dll!";
        }

        rklm_getprevbitmap=(RKLM_GETPREVBITMAP)rmc1lib->resolve("rklm_getprevbitmap");
        if(rklm_getprevbitmap==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getprevbitmap in MarkRkq.dll!";
        }

        rklm_getprevbitmapbyname=(RKLM_GETPREVBITMAPBYNAME)rmc1lib->resolve("rklm_getprevbitmapbyname");
        if(rklm_getprevbitmapbyname==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getprevbitmapbyname in MarkRkq.dll!";
        }

        rklm_getentsize=(RKLM_GETENTSIZE)rmc1lib->resolve("rklm_getentsize");
        if(rklm_getentsize==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getentsize in MarkRkq.dll!";
        }

        rklm_moveent=(RKLM_MOVEENT)rmc1lib->resolve("rklm_moveent");
        if(rklm_moveent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_moveent in MarkRkq.dll!";
        }

        rklm_scaleent=(RKLM_SCALEENT)rmc1lib->resolve("rklm_scaleent");
        if(rklm_scaleent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_scaleent in MarkRkq.dll!";
        }

        rklm_mirrorent=(RKLM_MIRRORENT)rmc1lib->resolve("rklm_mirrorent");
        if(rklm_mirrorent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_mirrorent in MarkRkq.dll!";
        }

        rklm_rotateent=(RKLM_ROTATEENT)rmc1lib->resolve("rklm_rotateent");
        if(rklm_rotateent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_rotateent in MarkRkq.dll!";
        }

        rklm_copyent=(RKLM_COPYENT)rmc1lib->resolve("rklm_copyent");
        if(rklm_copyent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_copyent in MarkRkq.dll!";
        }

        rklm_getentitycount=(RKLM_GETENTITYCOUNT)rmc1lib->resolve("rklm_getentitycount");
        if(rklm_getentitycount==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getentitycount in MarkRkq.dll!";
        }

        rklm_getentityname=(RKLM_GETENTITYNAME)rmc1lib->resolve("rklm_getentityname");
        if(rklm_getentityname==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getentityname in MarkRkq.dll!";
        }

        rklm_setentityname=(RKLM_SETENTITYNAME)rmc1lib->resolve("rklm_setentityname");
        if(rklm_setentityname==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setentityname in MarkRkq.dll!";
        }

        rklm_changeentname=(RKLM_CHANGEENTNAME)rmc1lib->resolve("rklm_changeentname");
        if(rklm_changeentname==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_changeentname in MarkRkq.dll!";
        }

        rklm_changetextbyname=(RKLM_CHANGETEXTBYNAME)rmc1lib->resolve("rklm_changetextbyname");
        if(rklm_changetextbyname==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_changetextbyname in MarkRkq.dll!";
        }

        rklm_gettextbyname=(RKLM_GETTEXTBYNAME)rmc1lib->resolve("rklm_gettextbyname");
        if(rklm_gettextbyname==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_gettextbyname in MarkRkq.dll!";
        }

        rklm_textresetsn=(RKLM_TEXTRESETSN)rmc1lib->resolve("rklm_textresetsn");
        if(rklm_textresetsn==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_textresetsn in MarkRkq.dll!";
        }

        rklm_groupent=(RKLM_GROUPENT)rmc1lib->resolve("rklm_groupent");
        if(rklm_groupent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_groupent in MarkRkq.dll!";
        }

        rklm_ungroupent=(RKLM_UNGROUPENT)rmc1lib->resolve("rklm_ungroupent");
        if(rklm_ungroupent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_ungroupent in MarkRkq.dll!";
        }

        rklm_groupent2=(RKLM_GROUPENT2)rmc1lib->resolve("rklm_groupent2");
        if(rklm_groupent2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_groupent2 in MarkRkq.dll!";
        }

        rklm_moveentitybefore=(RKLM_MOVEENTITYBEFORE)rmc1lib->resolve("rklm_moveentitybefore");
        if(rklm_moveentitybefore==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_moveentitybefore in MarkRkq.dll!";
        }

        rklm_moveentityafter=(RKLM_MOVEENTITYAFTER)rmc1lib->resolve("rklm_moveentityafter");
        if(rklm_moveentityafter==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_moveentityafter in MarkRkq.dll!";
        }

        rklm_reverseallentorder=(RKLM_REVERSEALLENTORDER)rmc1lib->resolve("rklm_reverseallentorder");
        if(rklm_reverseallentorder==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_reverseallentorder in MarkRkq.dll!";
        }

        rklm_getbitmapentparam=(RKLM_GETBITMAPENTPARAM)rmc1lib->resolve("rklm_getbitmapentparam");
        if(rklm_getbitmapentparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getbitmapentparam in MarkRkq.dll!";
        }

        rklm_gettextentparam=(RKLM_GETTEXTENTPARAM)rmc1lib->resolve("rklm_gettextentparam");
        if(rklm_gettextentparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_gettextentparam in MarkRkq.dll!";
        }

        rklm_settextentparam=(RKLM_SETTEXTENTPARAM)rmc1lib->resolve("rklm_settextentparam");
        if(rklm_settextentparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_settextentparam in MarkRkq.dll!";
        }

        rklm_deleteent=(RKLM_DELETEENT)rmc1lib->resolve("rklm_deleteent");
        if(rklm_deleteent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_deleteent in MarkRkq.dll!";
        }

        rklm_clearentlib=(RKLM_CLEARENTLIB)rmc1lib->resolve("rklm_clearentlib");
        if(rklm_clearentlib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_clearentlib in MarkRkq.dll!";
        }

        rklm_addtexttolib=(RKLM_ADDTEXTTOLIB)rmc1lib->resolve("rklm_addtexttolib");
        if(rklm_addtexttolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_addtexttolib in MarkRkq.dll!";
        }

        rklm_addcircletexttolib=(RKLM_ADDCIRCLETEXTTOLIB)rmc1lib->resolve("rklm_addcircletexttolib");
        if(rklm_addcircletexttolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_addcircletexttolib in MarkRkq.dll!";
        }

        rklm_getcircletextparam=(RKLM_GETCIRCLETEXTPARAM)rmc1lib->resolve("rklm_getcircletextparam");
        if(rklm_getcircletextparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getcircletextparam in MarkRkq.dll!";
        }

        rklm_setcircletextparam=(RKLM_SETCIRCLETEXTPARAM)rmc1lib->resolve("rklm_setcircletextparam");
        if(rklm_setcircletextparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setcircletextparam in MarkRkq.dll!";
        }

        rklm_addfiletolib=(RKLM_ADDFILETOLIB)rmc1lib->resolve("rklm_addfiletolib");
        if(rklm_addfiletolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_addfiletolib in MarkRkq.dll!";
        }

        rklm_addcurvetolib=(RKLM_ADDCURVETOLIB)rmc1lib->resolve("rklm_addcurvetolib");
        if(rklm_addcurvetolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_addcurvetolib in MarkRkq.dll!";
        }

        rklm_addcurvetolib2=(RKLM_ADDCURVETOLIB2)rmc1lib->resolve("rklm_addcurvetolib2");
        if(rklm_addcurvetolib2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_addcurvetolib2 in MarkRkq.dll!";
        }

        rklm_adddelaytolib=(RKLM_ADDDELAYTOLIB)rmc1lib->resolve("rklm_adddelaytolib");
        if(rklm_adddelaytolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_adddelaytolib in MarkRkq.dll!";
        }

        rklm_adddwriteporttolib=(RKLM_ADDWRITEPORTTOLIB)rmc1lib->resolve("rklm_adddwriteporttolib");
        if(rklm_adddwriteporttolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_adddwriteporttolib in MarkRkq.dll!";
        }
        rklm_addbarcodetolib=(RKLM_ADDBARCODETOLIB)rmc1lib->resolve("rklm_addbarcodetolib");
        if(rklm_addbarcodetolib==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_addbarcodetolib in MarkRkq.dll!";
        }

        rklm_getbarcodeparam=(RKLM_GETBARCODEPARAM)rmc1lib->resolve("rklm_getbarcodeparam");
        if(rklm_getbarcodeparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getbarcodeparam in MarkRkq.dll!";
        }

        rklm_setbarcodeparam=(RKLM_SETBARCODEPARAM)rmc1lib->resolve("rklm_setbarcodeparam");
        if(rklm_setbarcodeparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setbarcodeparam in MarkRkq.dll!";
        }

        rklm_readport=(RKLM_READPORT)rmc1lib->resolve("rklm_readport");
        if(rklm_readport==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_readport in MarkRkq.dll!";
        }

        rklm_getoutport = (RKLM_GETOUTPORT)rmc1lib->resolve("rklm_getoutport");
        if (rklm_getoutport == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getoutport in MarkRkq.dll!";
        }

        rklm_writeport=(RKLM_WRITEPORT)rmc1lib->resolve("rklm_writeport");
        if(rklm_writeport==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_writeport in MarkRkq.dll!";
        }

        rklm_gethatchparam3=(RKLM_GETHATCHPARAM3)rmc1lib->resolve("rklm_gethatchparam3");
        if(rklm_gethatchparam3==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_gethatchparam3 in MarkRkq.dll!";
        }

        rklm_sethatchparam3=(RKLM_SETHATCHPARAM3)rmc1lib->resolve("rklm_sethatchparam3");
        if(rklm_sethatchparam3==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_sethatchparam3 in MarkRkq.dll!";
        }

        rklm_gethatchentparam2=(RKLM_GETHATCHENTPARAM2)rmc1lib->resolve("rklm_gethatchentparam2");
        if(rklm_gethatchentparam2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_gethatchentparam2 in MarkRkq.dll!";
        }

        rklm_sethatchentparam2=(RKLM_SETHATCHENTPARAM2)rmc1lib->resolve("rklm_sethatchentparam2");
        if(rklm_sethatchentparam2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_sethatchentparam2 in MarkRkq.dll!";
        }

        rklm_hatchent=(RKLM_HATCHENT)rmc1lib->resolve("rklm_hatchent");
        if(rklm_hatchent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_hatchent in MarkRkq.dll!";
        }

        rklm_unhatchent=(RKLM_UNHATCHENT)rmc1lib->resolve("rklm_unhatchent");
        if(rklm_unhatchent==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_unhatchent in MarkRkq.dll!";
        }

        rklm_getfontparam3=(RKLM_GETFONTPARAM3)rmc1lib->resolve("rklm_getfontparam3");
        if(rklm_getfontparam3==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getfontparam3 in MarkRkq.dll!";
        }

        rklm_setfontparam3=(RKLM_SETFONTPARAM3)rmc1lib->resolve("rklm_setfontparam3");
        if(rklm_setfontparam3==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setfontparam3 in MarkRkq.dll!";
        }

        rklm_getfontrecordcount=(RKLM_GETFONTRECORDCOUNT)rmc1lib->resolve("rklm_getfontrecordcount");
        if(rklm_getfontrecordcount==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getfontrecordcount in MarkRkq.dll!";
        }

        rklm_getallfontrecord = (RKLM_GETALLFONTRECORD)rmc1lib->resolve("rklm_getallfontrecord");
        if (rklm_getallfontrecord == nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getallfontrecord in MarkRkq.dll!";
        }

        rklm_getpenparam=(RKLM_GETPENPARAM)rmc1lib->resolve("rklm_getpenparam");
        if(rklm_getpenparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getpenparam in MarkRkq.dll!";
        }

        rklm_setpenparam=(RKLM_SETPENPARAM)rmc1lib->resolve("rklm_setpenparam");
        if(rklm_setpenparam==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setpenparam in MarkRkq.dll!";
        }

        rklm_getpenparam2=(RKLM_GETPENPARAM2)rmc1lib->resolve("rklm_getpenparam2");
        if(rklm_getpenparam2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getpenparam2 in MarkRkq.dll!";
        }

        rklm_setpenparam2=(RKLM_SETPENPARAM2)rmc1lib->resolve("rklm_setpenparam2");
        if(rklm_setpenparam2==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setpenparam2 in MarkRkq.dll!";
        }

        rklm_getpenparam4=(RKLM_GETPENPARAM4)rmc1lib->resolve("rklm_getpenparam4");
        if(rklm_getpenparam4==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getpenparam4 in MarkRkq.dll!";
        }

        rklm_setpenparam4=(RKLM_SETPENPARAM4)rmc1lib->resolve("rklm_setpenparam4");
        if(rklm_setpenparam4==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setpenparam4 in MarkRkq.dll!";
        }




        rklm_axismoveto=(RKLM_AXISMOVETO)rmc1lib->resolve("rklm_axismoveto");
        if(rklm_axismoveto==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_axismoveto in MarkRkq.dll!";
        }

        rklm_axiscorrectorigin=(RKLM_AXISCORRECTORIGIN)rmc1lib->resolve("rklm_axiscorrectorigin");
        if(rklm_axiscorrectorigin==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_axiscorrectorigin in MarkRkq.dll!";
        }

        rklm_getaxiscoor=(RKLM_GETAXISCOOR)rmc1lib->resolve("rklm_getaxiscoor");
        if(rklm_getaxiscoor==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_getaxiscoor in MarkRkq.dll!";
        }


        rklm_setdevcfg3=(RKLM_SETDEVCFG3)rmc1lib->resolve("rklm_setdevcfg3");
        if(rklm_setdevcfg3==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setdevcfg3 in MarkRkq.dll!";
        }

        rklm_setdevcfg4=(RKLM_SETDEVCFG4)rmc1lib->resolve("rklm_setdevcfg4");
        if(rklm_setdevcfg3==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setdevcfg3 in MarkRkq.dll!";
        }

        rklm_isaxisrunning=(RKLM_ISAXISRUNNING)rmc1lib->resolve("rklm_isaxisrunning");
        if(rklm_isaxisrunning==nullptr)
        {
            qDebug() <<"Can not find funtion rklm_setdevcfg3 in MarkRkq.dll!";
        }

        rklm_prmmmark=(RKLM_PRMMMARK)rmc1lib->resolve("rklm_prmmmark");
        if(rklm_prmmmark==nullptr)
        {
            qDebug() <<"Can not find funtion RKLM_PRMMMARK in MarkRkq.dll!";
        }

//        rklm_getaxiscoorpulse=(RKLM_GETAXISCOORPULSE)rmc1lib->resolve("rklm_getaxiscoorpulse");
//        if(rklm_getaxiscoorpulse==nullptr)
//        {
//            qDebug() <<"Can not find funtion RKLM_GETAXISCOORPULSE in MarkRkq.dll!";
//        }

//        rklm_axismovetopulse=(RKLM_AXISMOVETOPULSE)rmc1lib->resolve("rklm_axismovetopulse");
//        if(rklm_axismovetopulse==nullptr)
//        {
//            qDebug() <<"Can not find funtion RKLM_AXISMOVETOPULSE in MarkRkq.dll!";
//        }

        rklm_visionpointsinput=(RKLM_VISIONPOINTSINPUT)rmc1lib->resolve("rklm_visionpointsinput");
        if(rklm_visionpointsinput==nullptr)
        {
            qDebug() <<"Can not find funtion RKLM_VISIONPOINTSINPUT in MarkRkq.dll!";
        }

//        rklm_reset=(RKLM_RESET)rmc1lib->resolve("rklm_reset");
//        if(rklm_reset==nullptr)
//        {
//            qDebug() <<"Can not find funtion RKLM_VISIONPOINTSINPUT in MarkRkq.dll!";
//        }

        rklm_ormmmark=(RKLM_ORMMMARK)rmc1lib->resolve("rklm_ormmmark");
        if(rklm_ormmmark==nullptr)
        {
            qDebug() <<"Can not find funtion RKLM_VISIONPOINTSINPUT in MarkRkq.dll!";
        }


    }
    return true;
}

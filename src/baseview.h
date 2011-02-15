/***************************************************************************
 *   Copyright (C) 2010 by Andres Cabrera                                  *
 *   mantaraya36@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QtGui>
#include "highlighter.h"
#include "scoreeditor.h"

class TextEditor;
class OpEntryParser;

class BaseView : public QScrollArea
{
  Q_OBJECT
  public:
    explicit BaseView(QWidget *parent, OpEntryParser *opcodeTree);
    ~BaseView();

    void setFullText(QString text, bool goToTop = false);
    void setBasicText(QString text);
    void setFileType(int mode); // For higlighting mode
    void setFont(QFont font);
    void setFontPointSize(float size);
    void setTabStopWidth(int width);
    void setLineWrapMode(QTextEdit::LineWrapMode mode);
    void setAutoComplete(bool autoComplete);
    void setColorVariables(bool color);
    void setBackgroundColor(QColor color);
//    void setOpcodeNameList(QStringList list);
//    void setOpcodeTree(OpEntryParser *opcodeTree);
    void setOrc(QString text);
    void setSco(QString text);
    void setFileB(QString text);
    void setLadspaText(QString text);

    QString getBasicText();  // What Csound needs (no widgets, misc text, etc.)

  signals:

  public slots:
  protected:
    void hideAllEditors();

    int m_mode; //type of text 0=csound 1=python 2=xml 3=orc 4=sco   -1=anything else
    int m_viewMode; // 0 = csd without widget + preset section
                    // 1 = full plain text
                    // From here on, you can have an or'd combination
                    // 2 = show CsInstruments Section
                    // 4 = show CsScore Section
                    // 8 = show CsOptions Section
                    // 16 = show <CsFileB> Section(s)
                    // 32 = show <CsVersion> Section(s)
                    // 64 = show <CsLicence>/<CsLicense> Section(s)
                    //128 = show remaining Text outside CsoundSynthesizer tag
                    //256 = show remaining text inside CsoundSynthesizer tag
                    //512 = show Widget, Preset and Extra Options sections
                    //1024 = show <CsLadspa> text with tags
    Highlighter m_highlighter;
    OpEntryParser *m_opcodeTree;
    QSplitter *splitter;
    TextEditor *mainEditor;
    ScoreEditor *scoreEditor;
    TextEditor *optionsEditor;
    TextEditor *filebEditor;
    TextEditor *versionEditor;
    TextEditor *licenceEditor;
    TextEditor *otherCsdEditor;  // Extra text and tags inside CsoundSynthesizer tags
    TextEditor *otherEditor;  // Extra text after removing all sections. All this text is to be presented at the start of the csd
    TextEditor *widgetEditor;
    TextEditor *ladspaEditor;
    QVector<QWidget *> editors; // A vector to hold pointers for the above for easy processing
};

#endif // BASEVIEW_H

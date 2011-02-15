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

#include "baseview.h"
#include "highlighter.h"
#include "texteditor.h"
#include "opentryparser.h"

BaseView::BaseView(QWidget *parent, OpEntryParser *opcodeTree) :
    QScrollArea(parent), m_opcodeTree(opcodeTree)
{
  mainEditor = new TextEditor(this);
  scoreEditor = new ScoreEditor(this);
  optionsEditor = new TextEditor(this);
  filebEditor = new TextEditor(this);
  versionEditor = new TextEditor(this);
  licenceEditor = new TextEditor(this);
  otherEditor = new TextEditor(this);
  otherCsdEditor = new TextEditor(this);
  widgetEditor = new TextEditor(this);
  ladspaEditor = new TextEditor(this);
  editors << mainEditor << scoreEditor << optionsEditor << filebEditor
      << versionEditor << licenceEditor << otherEditor << otherCsdEditor << widgetEditor
      << ladspaEditor;

  splitter = new QSplitter(this);
  splitter->setOrientation(Qt::Vertical);
  splitter->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  splitter->setContextMenuPolicy (Qt::NoContextMenu);

  QStackedLayout *l = new QStackedLayout(this);
  l->addWidget(splitter);
  setLayout(l);
  m_mode = 0;
  m_highlighter.setOpcodeNameList(opcodeTree->opcodeNameList());
  m_highlighter.setDocument(mainEditor->document());
}

BaseView::~BaseView()
{

}

void BaseView::setFullText(QString text, bool goToTop)
{
  if (m_viewMode < 2) {  // Unified view
    QTextCursor cursor = mainEditor->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.insertText(text);
    mainEditor->setTextCursor(cursor);  // TODO implement for multiple views
    if (goToTop) {
      mainEditor->moveCursor(QTextCursor::Start);
    }
  }
  else { // Split view
    int startIndex,endIndex;
    QString sectionText = "";
    // Find orchestra section
    startIndex = text.indexOf("<CsInstruments>");
    if (text.size() > startIndex + 1 && text[startIndex+1] == '\n') {
      startIndex++;
    }
    endIndex = text.indexOf("</CsInstruments>") + 16;
    if (text.size() > endIndex + 1 && text[endIndex+1] == '\n') {
      endIndex++;
    }
    if (endIndex > startIndex) {
      sectionText = text.mid(startIndex, endIndex - startIndex);
    }
    text.remove(sectionText);
    setOrc(sectionText.mid(15, sectionText.size() - 15 - 16));
    // Find score section
    sectionText = "";
    startIndex = text.indexOf("<CsScore>");
    if (text.size() > startIndex + 1 && text[startIndex+1] == '\n') {
      startIndex++;
    }
    endIndex = text.indexOf("</CsScore>") + 10;
    if (text.size() > endIndex + 1 && text[endIndex+1] == '\n') {
      endIndex++;
    }
    if (endIndex > startIndex) {
      sectionText = text.mid(startIndex, endIndex - startIndex);
    }
    text.remove(sectionText);
    setSco(sectionText.mid(9, sectionText.size() - 9 - 10));
    // Find ladspa section
    sectionText = "";
    startIndex = text.indexOf("<csLADSPA>");
    if (text.size() > startIndex + 1 && text[startIndex+1] == '\n') {
      startIndex++;
    }
    endIndex = text.indexOf("</csLADSPA>") + 11;
    if (text.size() > endIndex + 1 && text[endIndex+1] == '\n') {
      endIndex++;
    }
    if (endIndex > startIndex) {
      sectionText = text.mid(startIndex, endIndex - startIndex);
    }
    text.remove(sectionText);
    setLadspaText(sectionText.mid(10, sectionText.size() - 10 - 11));
    // Find File section
    sectionText = "";
    startIndex = text.indexOf("<csLADSPA>");
    if (text.size() > startIndex + 1 && text[startIndex+1] == '\n') {
      startIndex++;
    }
    endIndex = text.indexOf("</csLADSPA>") + 11;
    if (text.size() > endIndex + 1 && text[endIndex+1] == '\n') {
      endIndex++;
    }
    if (endIndex > startIndex) {
      sectionText = text.mid(startIndex, endIndex - startIndex);
    }
    text.remove(sectionText);
    setLadspaText(sectionText.mid(10, sectionText.size() - 10 - 11));
  }

//  void setFileB(QString text);
//  void setLadspaText(QString text);
}

void BaseView::setBasicText(QString text)
{
  QTextCursor cursor = mainEditor->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.insertText(text);
  mainEditor->setTextCursor(cursor);  // TODO implement for multiple views
}

void BaseView::setFileType(int mode)
{
  m_highlighter.setMode(mode);
  m_mode = mode;
}

void BaseView::setFont(QFont font)
{
  mainEditor->setFont(font);
  scoreEditor->setFont(font);
  optionsEditor->setFont(font);
  filebEditor->setFont(font);
  versionEditor->setFont(font);
  licenceEditor->setFont(font);
  otherEditor->setFont(font);
  otherCsdEditor->setFont(font);
  widgetEditor->setFont(font);
  ladspaEditor->setFont(font);
}

void BaseView::setFontPointSize(float size)
{
  mainEditor->setFontPointSize(size);
  scoreEditor->setFontPointSize(size);
  optionsEditor->setFontPointSize(size);
  filebEditor->setFontPointSize(size);
  versionEditor->setFontPointSize(size);
  licenceEditor->setFontPointSize(size);
  otherEditor->setFontPointSize(size);
  otherCsdEditor->setFontPointSize(size);
  widgetEditor->setFontPointSize(size);
  ladspaEditor->setFontPointSize(size);
}

void BaseView::setTabStopWidth(int width)
{
  mainEditor->setTabStopWidth(width);
  scoreEditor->setTabStopWidth(width);
  optionsEditor->setTabStopWidth(width);
  filebEditor->setTabStopWidth(width);
  versionEditor->setTabStopWidth(width);
  licenceEditor->setTabStopWidth(width);
  otherEditor->setTabStopWidth(width);
  otherCsdEditor->setTabStopWidth(width);
  widgetEditor->setTabStopWidth(width);
  ladspaEditor->setTabStopWidth(width);
}

void BaseView::setLineWrapMode(QTextEdit::LineWrapMode mode)
{
  mainEditor->setLineWrapMode(mode);
  scoreEditor->setLineWrapMode(mode);
  optionsEditor->setLineWrapMode(mode);
  filebEditor->setLineWrapMode(mode);
  versionEditor->setLineWrapMode(mode);
  licenceEditor->setLineWrapMode(mode);
  otherEditor->setLineWrapMode(mode);
  otherCsdEditor->setLineWrapMode(mode);
  widgetEditor->setLineWrapMode(mode);
  ladspaEditor->setLineWrapMode(mode);
}

void BaseView::setColorVariables(bool color)
{
  m_highlighter.setColorVariables(color);
}

void BaseView::setBackgroundColor(QColor color)
{
  QPalette p = mainEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  mainEditor->setPalette(p);
  p = scoreEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  scoreEditor->setPalette(p);
  p = optionsEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  optionsEditor->setPalette(p);
  p = filebEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  filebEditor->setPalette(p);
  p = versionEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  versionEditor->setPalette(p);
  p = licenceEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  licenceEditor->setPalette(p);
  p = otherCsdEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  otherCsdEditor->setPalette(p);
  p = otherEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  otherEditor->setPalette(p);
  p = widgetEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  widgetEditor->setPalette(p);
  p = ladspaEditor->palette();
  p.setColor(static_cast<QPalette::ColorRole>(9), color);
  ladspaEditor->setPalette(p);
}

void BaseView::setOrc(QString text)
{
  if (m_viewMode < 2) { // View is not split
    if (m_mode != 0) {
      qDebug() << "DocumentView::setOrc Current file is not a csd file. Text not inserted!";
      return;
    }
    QString csdText = getBasicText();
    if (csdText.contains("<CsInstruments>") and csdText.contains("</CsInstruments>")) {
      QString preText = csdText.mid(0, csdText.indexOf("<CsInstruments>") + 15);
      QString postText = csdText.mid(csdText.lastIndexOf("</CsInstruments>"));
      if (!text.startsWith("\n")) {
        text.prepend("\n");
      }
      if (!text.endsWith("\n")) {
        text.append("\n");
      }
      csdText = preText + text + postText;
      setBasicText(csdText);
    }
    else {
      qDebug() << "DocumentView::setOrc Orchestra section not found in csd. Text not inserted!";
    }
  }
  else {
    mainEditor->setPlainText(text);
  }
}

void BaseView::setSco(QString text)
{
  if (m_viewMode < 2) { // View is not split
    if (m_mode != 0) {
      qDebug() << "DocumentView::setSco Current file is not a csd file. Text not inserted!";
      return;
    }
    QString csdText = getBasicText();
    if (csdText.contains("<CsScore>") and csdText.contains("</CsScore>")) {
      QString preText = csdText.mid(0, csdText.indexOf("<CsScore>") + 9);
      QString postText = csdText.mid(csdText.lastIndexOf("</CsScore>"));
      if (!text.startsWith("\n")) {
        text.prepend("\n");
      }
      if (!text.endsWith("\n")) {
        text.append("\n");
      }
      csdText = preText + text + postText;
      setBasicText(csdText);
    }
    else {
      qDebug() << "DocumentView::setSco Orchestra section not found in csd. Text not inserted!";
    }
  }
  else {
    scoreEditor->setPlainText(text);
  }
}

void BaseView::setFileB(QString text)
{
  filebEditor->setPlainText(text);
}

void BaseView::setLadspaText(QString text)
{
  if (m_viewMode < 2) { // View is not split
    if (m_mode != 0) {
      qDebug() << "DocumentView::setLadspaText Current file is not a csd file. Text not inserted!";
      return;
    }
    QTextCursor cursor;
    cursor = mainEditor->textCursor();
    mainEditor->moveCursor(QTextCursor::Start);
    if (mainEditor->find("<csLADSPA>") and mainEditor->find("</csLADSPA>")) {
      QString curText = getBasicText();
      int index = curText.indexOf("<csLADSPA>");
      int endIndex = curText.indexOf("</csLADSPA>") + 11;
      if (curText.size() > endIndex + 1 && curText[endIndex + 1] == '\n') {
        endIndex++; // Include last line break
      }
      curText.remove(index, endIndex - index);
      curText.insert(index, text);
      setBasicText(curText);
      mainEditor->moveCursor(QTextCursor::Start);
    }
    else { //csLADSPA section not present, or incomplete
      mainEditor->find("<CsoundSynthesizer>"); //cursor moves there
      mainEditor->moveCursor(QTextCursor::EndOfLine);
      mainEditor->insertPlainText(QString("\n") + text + QString("\n"));
    }
  }
  else {
    ladspaEditor->setText(text);
    ladspaEditor->moveCursor(QTextCursor::Start);
  }
}


QString BaseView::getBasicText()
{
//   What Csound needs (no widgets, misc text, etc.)
  // TODO implement modes
  QString text;
  text = mainEditor->toPlainText(); // csd without extra sections
  if (m_viewMode & 16) {
    text += filebEditor->toPlainText();
  }
  return text;
}

//void BaseView::setOpcodeNameList(QStringList list)
//{
//  m_highlighter.setOpcodeNameList(list);
//}

//void BaseView::setOpcodeTree(OpEntryParser *opcodeTree)
//{
//  m_opcodeTree = opcodeTree;
//}

void BaseView::hideAllEditors()
{
    mainEditor->hide();
    scoreEditor->hide();
    optionsEditor->hide();
    filebEditor->hide();
    versionEditor->hide();
    licenceEditor->hide();
    otherEditor->hide();
    otherCsdEditor->hide();
    widgetEditor->hide();
    ladspaEditor->hide();
    for (int i = 0; i < 9; i++) {
      QSplitterHandle *h = splitter->handle(i);
      if (h) {
        h->hide();
      }
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QQuickItem>
#include <iostream>
#include <QTimer>
#include <QFile>
#include <QStyle>
#include <QDebug>
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mOmitSignal(false)
{
    qmlRegisterType<BitRegister>("emsec.feistel.bitregister", 1, 0, "BitRegister");
    mMessageBits    = new BitRegister(32);
    mRoundKeyBits   = new BitRegister(48, 0xFFAA55332210);
    mExpandedBits   = new BitRegister(48);
    mSboxInputBits  = new BitRegister(48);
    mSboxOutputBits = new BitRegister(32);
    mFeistelFuncBits    = new BitRegister(32);
    for (int i=0; i<numberFeistelBoxes; i++)
        mSBox[i] = SBox::feistelFactory(i);

    connect(mMessageBits,   &BitRegister::bitRegChanged, this, &MainWindow::handleMessageChanged);
    connect(mRoundKeyBits,  &BitRegister::bitRegChanged, this, &MainWindow::handleRoundKeyChanged);
    connect(mSboxInputBits, &BitRegister::bitRegChanged, this, &MainWindow::handleSboxInputChanged);
    connect(mFeistelFuncBits,   &BitRegister::bitRegChanged, this, &MainWindow::handleFeistelFuncChanged);
    ui->setupUi(this);
    ui->quickWidget->rootContext()->setContextProperty("messageBits", mMessageBits);
    ui->quickWidget->rootContext()->setContextProperty("roundKeyBits", mRoundKeyBits);
    ui->quickWidget->rootContext()->setContextProperty("expandedBits", mExpandedBits);
    ui->quickWidget->rootContext()->setContextProperty("sboxInputBits", mSboxInputBits);
    ui->quickWidget->rootContext()->setContextProperty("sboxOutputBits", mSboxOutputBits);
    ui->quickWidget->rootContext()->setContextProperty("feistelFuncBits", mFeistelFuncBits);
    applyStyle("dark");
    handleMessageChanged();
    handleRoundKeyChanged();
}

MainWindow::~MainWindow()
{
    for (int i=0; i<numberFeistelBoxes; i++)
        delete mSBox[i];
    delete ui;
}
void MainWindow::on_actionDark_triggered()
{
    applyStyle("dark");
}

void MainWindow::on_actionLight_triggered()
{
    applyStyle("light");
}

void MainWindow::on_actionInvertMsg_triggered()
{
    mMessageBits->invert();
}

void MainWindow::on_actionInvertKey_triggered()
{
    mRoundKeyBits->invert();
}

void MainWindow::emitTriggerRepaint()
{
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "triggerRepaint");
}

void MainWindow::applyStyle(const QString& name)
{
    QFile fqss(":/qss/" + name + ".qss");
    if (!fqss.open(QIODevice::ReadOnly)) return;
    qApp->setStyleSheet(fqss.readAll());
    QStyle* sty = style();
    sty->unpolish(this);
    sty->polish(this);
    emitTriggerRepaint();
}

void MainWindow::setColorHighState(const QColor& c)
{
    mColorHighState = c;
    Q_EMIT colorHighStateChanged();
    ui->quickWidget->rootObject()->setProperty("colorHighState", mColorHighState);
}

void MainWindow::setColorLowState(const QColor& c)
{
    mColorLowState = c;
    Q_EMIT colorLowStateChanged();
    ui->quickWidget->rootObject()->setProperty("colorLowState", mColorLowState);
}

void MainWindow::setColorBackground(const QColor& c)
{
    mColorBackground = c;
    Q_EMIT colorBackgroundChanged();
    ui->quickWidget->rootObject()->setProperty("colorBackground", mColorBackground);
}

void MainWindow::setColorNeutral(const QColor &c)
{
    mColorNeutral = c;
    Q_EMIT colorNeutralChanged();
    ui->quickWidget->rootObject()->setProperty("colorNeutral", mColorNeutral);
}

void MainWindow::setColorText(const QColor &c)
{
    mColorText = c;
    Q_EMIT colorTextChanged();
    ui->quickWidget->rootObject()->setProperty("colorText", mColorText);
}

void MainWindow::setColorSbox(const QColor &c)
{
    mColorSbox = c;
    Q_EMIT colorSboxChanged();
    ui->quickWidget->rootObject()->setProperty("colorSbox", mColorSbox);
}

void MainWindow::handleMessageChanged()
{
    mOmitSignal = true;
    QSpinBox* msgSpinBox[4] = { ui->spinMsg0, ui->spinMsg1, ui->spinMsg2, ui->spinMsg3 };
    for (int i=0; i<4; i++)
        msgSpinBox[i]->setValue(mMessageBits->getBits(i*8,8));
    mExpandedBits->setPermutationResult(mMessageBits, PermutationTable::expansion);
    mSboxInputBits->setXorResult(mExpandedBits, mRoundKeyBits);
    emitTriggerRepaint();
    mOmitSignal = false;
}

void MainWindow::handleRoundKeyChanged()
{
    mOmitSignal = true;
    QSpinBox* keySpinBox[6] = { ui->spinKey0, ui->spinKey1, ui->spinKey2, ui->spinKey3, ui->spinKey4, ui->spinKey5 };
    for (int i=0; i<6; i++)
        keySpinBox[i]->setValue(mRoundKeyBits->getBits(i*8,8));
    mSboxInputBits->setXorResult(mExpandedBits, mRoundKeyBits);
    emitTriggerRepaint();
    mOmitSignal = false;
}

void MainWindow::handleSboxInputChanged() {
    for (int i=0; i<numberFeistelBoxes; i++)
    {
        quint8 input = mSboxInputBits->getBits(i*6,6);
        quint8 output = mSBox[i]->lookup(input);
        mSboxOutputBits->setBits(i*4,4,output);
        mFeistelFuncBits->setPermutationResult(mSboxOutputBits, PermutationTable::final);
    }
}

void MainWindow::handleFeistelFuncChanged() {
    QLabel* encLabel[4] = { ui->valEnc0, ui->valEnc1, ui->valEnc2, ui->valEnc3 };
    for (int i=0; i<4; i++)
    {
        quint8 ffByte = mFeistelFuncBits->getBits(i*8, 8);
        encLabel[i]->setText(QString::number(ffByte,16));
    }
}

void MainWindow::on_spinMsg0_valueChanged(int msgByte)
{
    if (mOmitSignal) return;
    mMessageBits->setBits(0, 8, (quint8) msgByte);
}

void MainWindow::on_spinMsg1_valueChanged(int msgByte)
{
    if (mOmitSignal) return;
    mMessageBits->setBits(8, 8, (quint8) msgByte);
}


void MainWindow::on_spinMsg2_valueChanged(int msgByte)
{
    if (mOmitSignal) return;
    mMessageBits->setBits(16, 8, (quint8) msgByte);
}


void MainWindow::on_spinMsg3_valueChanged(int msgByte)
{
    if (mOmitSignal) return;
    mMessageBits->setBits(24, 8, (quint8) msgByte);
}


void MainWindow::on_spinKey0_valueChanged(int keyByte)
{
    if (mOmitSignal) return;
    mRoundKeyBits->setBits(0, 8, (quint8) keyByte);
}

void MainWindow::on_spinKey1_valueChanged(int keyByte)
{
    if (mOmitSignal) return;
    mRoundKeyBits->setBits(8, 8, (quint8) keyByte);
}

void MainWindow::on_spinKey2_valueChanged(int keyByte)
{
    if (mOmitSignal) return;
    mRoundKeyBits->setBits(16, 8, (quint8) keyByte);
}

void MainWindow::on_spinKey3_valueChanged(int keyByte)
{
    if (mOmitSignal) return;
    mRoundKeyBits->setBits(24, 8, (quint8) keyByte);
}

void MainWindow::on_spinKey4_valueChanged(int keyByte)
{
    if (mOmitSignal) return;
    mRoundKeyBits->setBits(32, 8, (quint8) keyByte);
}

void MainWindow::on_spinKey5_valueChanged(int keyByte)
{
    if (mOmitSignal) return;
    mRoundKeyBits->setBits(40, 8, (quint8) keyByte);
}

/*
void MainWindow::handleMessageBitsChanged(int msg)
{
    mOmitSignal = true;
    quint32 umsg = msg;
    QSpinBox* msgByte[4] = {ui->spinMsg3, ui->spinMsg2, ui->spinMsg1, ui->spinMsg0 };
    for (int ibyte=0; ibyte<4; ibyte++)
    {
        msgByte[ibyte]->setValue(umsg&0xFF);
        umsg >>= 8;
    }
    mOmitSignal = false;
}
*/

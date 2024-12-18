#pragma once
#include <QMainWindow>
#include <QColor>
#include "bitregister.h"
#include "sbox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(QColor colorHighState READ colorHighState WRITE setColorHighState NOTIFY colorHighStateChanged);
    Q_PROPERTY(QColor colorLowState READ colorLowState WRITE setColorLowState NOTIFY colorLowStateChanged);
    Q_PROPERTY(QColor colorBackground READ colorBackground WRITE setColorBackground NOTIFY colorBackgroundChanged);
    Q_PROPERTY(QColor colorNeutral READ colorNeutral WRITE setColorNeutral NOTIFY colorNeutralChanged);
    Q_PROPERTY(QColor colorText READ colorText WRITE setColorText NOTIFY colorTextChanged);
    Q_PROPERTY(QColor colorSbox READ colorSbox WRITE setColorSbox NOTIFY colorSboxChanged);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QColor colorHighState()   const { return mColorHighState; }
    QColor colorLowState()    const { return mColorLowState; }
    QColor colorBackground()  const { return mColorBackground; }
    QColor colorNeutral()     const { return mColorNeutral; }
    QColor colorText()        const { return mColorText; }
    QColor colorSbox()        const { return mColorSbox; }
    void setColorHighState (const QColor& c);
    void setColorLowState  (const QColor& c);
    void setColorBackground(const QColor& c);
    void setColorNeutral   (const QColor& c);
    void setColorText      (const QColor& c);
    void setColorSbox      (const QColor& c);

Q_SIGNALS:
    void colorHighStateChanged();
    void colorLowStateChanged();
    void colorBackgroundChanged();
    void colorNeutralChanged();
    void colorTextChanged();
    void colorSboxChanged();

private Q_SLOTS:
    void on_spinMsg0_valueChanged(int msgByte);
    void on_spinMsg1_valueChanged(int msgByte);
    void on_spinMsg2_valueChanged(int msgByte);
    void on_spinMsg3_valueChanged(int msgByte);
    void on_spinKey0_valueChanged(int keyByte);
    void on_spinKey1_valueChanged(int keyByte);
    void on_spinKey2_valueChanged(int keyByte);
    void on_spinKey3_valueChanged(int keyByte);
    void on_spinKey4_valueChanged(int keyByte);
    void on_spinKey5_valueChanged(int keyByte);
    void on_actionDark_triggered();
    void on_actionLight_triggered();
    void on_actionInvertMsg_triggered();
    void on_actionInvertKey_triggered();
    void handleMessageChanged();
    void handleRoundKeyChanged();
    void handleSboxInputChanged();
    void handleFeistelFuncChanged();

private:
    Ui::MainWindow *ui;
    bool mOmitSignal;

    QColor mColorHighState;
    QColor mColorLowState;
    QColor mColorBackground;
    QColor mColorNeutral;
    QColor mColorText;
    QColor mColorSbox;

    BitRegister* mMessageBits;
    BitRegister* mRoundKeyBits;
    BitRegister* mExpandedBits;
    BitRegister* mSboxInputBits;
    BitRegister* mSboxOutputBits;
    BitRegister* mFeistelFuncBits;
    SBox* mSBox[numberFeistelBoxes];

    void applyStyle(const QString& name);
    void emitTriggerRepaint();
};

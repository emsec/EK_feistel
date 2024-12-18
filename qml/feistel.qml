import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.12
import emsec.feistel.bitregister 1.0

Rectangle {
    id : toplevel;
    property int   numberMsgBits    : 32;
    property int   numberKeyBits    : 48;
    signal triggerRepaint();

    property color colorHighState   : "#FF0000" ;
    property color colorLowState    : "#0080FF" ;
    property color colorBackground  : "#000000" ;
    property color colorNeutral     : "#505050" ;
    property color colorText        : "#FFFFFF" ;

    property color colorSbox        : "#505050" ;

    property variant expandRef : [
        32,  1,  2,  3,  4,  5,
        4,   5,  6,  7,  8,  9,
        8,   9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1
      ];

    property variant permutateRef : [
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    ];

//    width: numberMsgBits * 110 + 110;
    height: 280;
    visible: true;
    color: colorBackground;

    onColorBackgroundChanged: {
        // redraw everything
        // need to emit messageBitsChanged ?
    }

    function bitcolor(val)
    {
        if (val === 1) return colorHighState;
        if (val === 0) return colorLowState;
        return Qt.rgba(0.7, 0.71, 0.72, 1);
    }

    Row {

        id : originalMessage;
        x  : 5;
        y  : 15;
        height : 26;

        Text {
            width : 45;
            color : colorText;
            textFormat: Text.RichText;
            text  : "<b>R<sub>i</sub></b>";
        }

        Repeater {
            id : msgBitsRepeater;
            model: numberMsgBits;


            Rectangle {
                id: bitreg;
                width : 26;
                height : originalMessage.height;
                border.width : 1;
                border.color : "lightgray"
                color : "transparent";

                Rectangle {
                    id : bitstate;
                    x : 2
                    width : 22
                    height : 22
                    radius : 22
                    color : bitcolor(0);
                    anchors.verticalCenter: parent.verticalCenter;

                    Connections {
                        target : toplevel;
                        function onTriggerRepaint() {
                            bitstate.color = bitcolor(messageBits.getBit(index));
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (messageBits !== undefined) {
                            messageBits.toggleBit(index);
                        }
                    }
                }

            }
        }
    }

    Canvas {
        id : expandConnection;
        x : 35;
        y : originalMessage.y + originalMessage.height;
        width : 870;
        height : 109;
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.lineWidth = 3;
            for (var i=0; i<numberKeyBits; i++)
            {
                var j = expandRef[i] - 1;
                ctx.beginPath();
                ctx.strokeStyle = bitcolor(messageBits.getBit(j));
                ctx.moveTo(j*26+28, 0);
                ctx.lineTo(i*18+7, height);
                ctx.stroke();
            }
        }
        Connections {
            target: toplevel;
            function onTriggerRepaint() {
                expandConnection.requestPaint();
            }
        }
    }

    //---------------------- 56 bit expanded message --------------------------------------------------------
    Text {
        width : 25;
        x : 5;
        y : expandedMessage.y+4;
        color : colorText;
        textFormat: Text.RichText;
        text  : "<b>E</b>(R<sub>i</sub>)";
    }

    Row {
        id : expandedMessage;
        x  : 35;
        y  : expandConnection.y + expandConnection.height;
        height : 22;

        spacing: 5;


        Repeater {
            id : expandedMessageBits;
            model: numberKeyBits;

            Rectangle {
                id : expandedMessageBit;
                width : 13
                height : expandedMessage.height;
                radius : 8
                color : bitcolor(0);

                Connections {
                    target: toplevel;
                    function onTriggerRepaint() {
                        expandedMessageBit.color = bitcolor(expandedBits.getBit(index));
                    }
                }
            }
        }
    }

    //---------------------- 56 bit key ---------------------------------------------------------------------
    Image {
        id: keyImage;
        x : 5;
        y : roundKey.y + 5;
        width: 25;
        fillMode: Image.PreserveAspectFit;
        source: "qrc:/icons/key.svg";
        visible: false;

    }

    ColorOverlay{
        anchors.fill: keyImage;
        source: keyImage;
        color: colorText;
        antialiasing: true;
    }

    Row {
        id : roundKey;
        x : 35;
        y : expandedMessage.y + expandedMessage.height + 4;
        height : 22;

        spacing: 5;

        Repeater {
            id : roundkeyBits;
            model: numberKeyBits;

            Rectangle {
                id : roundkeyBit;
                width : 13;
                height : expandedMessage.height;
                radius : 8;
                color : bitcolor(0);

                Connections {
                    target: toplevel;
                    function onTriggerRepaint() {
                        roundkeyBit.color = bitcolor(roundKeyBits.getBit(index));
                    }
                }
            }
        }
    }

    //---------------------- horizontal line ----------------------------------------------------------------
    Canvas {
        id : xorLine;
        x : 10;
        y : roundKey.y + roundKey.height + 4;
        width : 870;
        height : 20;
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.strokeStyle = colorNeutral;
            ctx.lineWidth = 3;
            ctx.moveTo(0, 10);
            ctx.lineTo(width, 10);
            ctx.stroke();
        }
    }


    //---------------------- XOR 56 bit key + expanded message ----------------------------------------------
    Image {
        id: xorImage;
        x : 5;
        y : xorResult.y-5;
        width: 20;
        fillMode: Image.PreserveAspectFit;
        source: "qrc:/icons/xor.svg";
        visible: false;

    }

    ColorOverlay{
        anchors.fill: xorImage;
        source: xorImage;
        color: colorNeutral;
        antialiasing: true;
    }

    Row {
        id : xorResult;
        x : 35;
        y : xorLine.y + xorLine.height + 4;
        height : 32;

        spacing: 5;

        Repeater {
            id : xorResultBits;
            model: numberKeyBits;

            Column {
                id : xorResultBit;

                Rectangle {
                    id : xorResultBitState;
                    width : 13
                    height : 22
                    radius : 8
                    color : bitcolor(0);

                    Connections {
                        target: toplevel;
                        function onTriggerRepaint() {
                            xorResultBitState.color = bitcolor(sboxInputBits.getBit(index));
                        }
                    }
                }

                Rectangle {
                    x : 5;
                    id : xorBitConnect;
                    width : 3;
                    height : xorResult.height - xorResultBitState.height;
                    color: xorResultBitState.color;
                }
            }
        }
    }


    //---------------------- 8 SBOX permutation -------------------------------------------------------------

    Row {
        id : sBoxMagic;
        x : 35;
        y : xorResult.y + xorResult.height;
        spacing: 5
        height : 103;

        Repeater {
            id : sBoxes;
            model : numberKeyBits / 6;

            Rectangle {
                id : sBox;
                width : 103;
                height : sBoxMagic.height;
                color : colorSbox;

                Text {
                    color : colorText
                    anchors.centerIn: parent;
                    text : "S-box " + (index+1);
                }
            }
        }
    }

    //---------------------- SBOX permutation output --------------------------------------------------------
    Row {
        id : sBoxOutput;
        x : 53;
        y : sBoxMagic.y + sBoxMagic.height;
        height : 32;
        spacing : 41;
        Repeater {
            id : sBoxOutputBits;
            model : numberKeyBits / 6;

            Row {
                property int sboxIndex: index
                spacing : 5;
                Repeater {
                    id : sBoxOutputBit;
                    model : 4;

                    Column {
                        Rectangle {
                            x : 5;
                            id : sBoxOutputBitConnect;
                            width : 3;
                            height : sBoxOutput.height - sBoxOutputBitState.height;
                            color: sBoxOutputBitState.color;
                        }

                        Rectangle {
                            id : sBoxOutputBitState;
                            width : 13;
                            height : 22;
                            radius : 8;
                            color : bitcolor(0);
                            Connections {
                                target: toplevel;
                                function onTriggerRepaint() {
                                    sBoxOutputBitState.color = bitcolor(sboxOutputBits.getBit(sboxIndex*4+index));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Canvas {
        id : finalPermutation;
        x : 35;
        y : sBoxOutput.y + sBoxOutput.height;
        width : 870;
        height : 330;
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.lineWidth = 2;
            for (var i=0; i<numberMsgBits; i++)
            {
                var j = permutateRef[i] - 1;
                var j0 = Math.floor(j / 4);
                var j1 = j % 4;
                ctx.beginPath();
                ctx.strokeStyle = bitcolor(sboxOutputBits.getBit(j));
                ctx.moveTo(j0*108+j1*18+25, 0);
                ctx.lineTo(i*26+28, height);
                ctx.stroke();
            }
        }
        Connections {
            target: toplevel;
            function onTriggerRepaint() {
                finalPermutation.requestPaint();
            }
        }
    }

    //---------------------- Feistel function result --------------------------------------------------------
    Row {
        x : 5;
        y : finalPermutation.y + finalPermutation.height;

        Text {
            width : 45;
            color : colorText;
            textFormat: Text.RichText
            text  : "<b><i>f</i></b> (R<sub>i</sub>, k<sub>i</sub>)";
        }

        Repeater {
            id : feistelResultRepeater;
            model: numberMsgBits;


            Rectangle {
                id: feistelResultBit;
                width : 26;
                height : 26;
                border.width : 1;
                border.color : "lightgray"
                color : "transparent";


                Rectangle {
                    id : feistelResultBitState;
                    x : 2
                    width : 22
                    height : 22
                    radius : 22
                    color : bitcolor(0);
                    anchors.verticalCenter: parent.verticalCenter;
                    Connections {
                        target: toplevel;
                        function onTriggerRepaint() {
                            feistelResultBitState.color = bitcolor(feistelFuncBits.getBit(index));
                        }
                    }
                }
            }
        }
    }
}

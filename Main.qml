/* This file is generated and only relevant for integrating the project into a Qt 6 and cmake based
C++ project. */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import untitled1

Window {
    id: window
    width: 230
    height: 390
    visible: true
    color: "#000000"
    onHeightChanged: console.log(height)

    Calculator{
        id: calc
    }


    component RoundButton: Rectangle {
        id: button
        Layout.preferredWidth: 50
        Layout.preferredHeight: 50

        radius: width/2
        color: "#333333"
        property string text: ""
        property color textColor: "#FFFFFF"
        property color hoverColor: button.color

        Text {
            font.pointSize: 24
            color: button.textColor
            id: name
            text: button.text
            anchors.centerIn: button
        }



        property bool pressed: false

        Behavior on scale {
            NumberAnimation { duration: 80; easing.type: Easing.InOutQuad }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                calc.onNumberButtonPressed(button.text)
            }
        }
    }

    component RoundButtonOperation: RoundButton{
        id:op_button
        color: "#F1A33B"
        property string operation: op_button.text
        MouseArea{
            anchors.fill: parent
            onClicked: calc.onOperationButtonPressed(op_button.operation)
        }
    }

    component RoundButtonTool: RoundButton{
        color: "#A5A5A5"

    }

    component TextSpace: Rectangle{
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 100
        color: window.color

        Text {
            id: result
            text: "0"
            color: "white"


            font.pixelSize: 42
            fontSizeMode: Text.Fit

            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
            anchors.fill: parent
            anchors.margins: 4

            Connections{
                target: calc
                onExpressionChanged: function(newExpression){
                    result.text = newExpression;
                    }
            }
        }
    }


    GridLayout {
            id: layout
            anchors.fill: parent
            anchors.margins: 8
            columns: 4
            rows: 7
            rowSpacing: 6
            columnSpacing: 6

            TextSpace {Layout.columnSpan: 4; Layout.rowSpan: 2}

            RoundButtonTool{
                text: "AC"
                MouseArea{
                    anchors.fill: parent
                    onClicked: calc.onClearButtonPressed()
                }
            }
            RoundButtonTool{
                text: "⌫"
                MouseArea{
                    anchors.fill: parent
                    onClicked: calc.onBackspaceButtonPressed()
                }

            }
            RoundButtonTool{
                text: "%"
                MouseArea{
                    anchors.fill: parent
                    onClicked: calc.onOperationButtonPressed('%')
                }
            }
            RoundButtonOperation { text: "÷"; operation: "/" }


            RoundButton { text: "7" }
            RoundButton { text: "8" }
            RoundButton { text: "9" }
            RoundButtonOperation { text: "*" }


            RoundButton { text: "4" }
            RoundButton { text: "5" }
            RoundButton { text: "6" }
            RoundButtonOperation { text: "-" }


            RoundButton { text: "1" }
            RoundButton { text: "2" }
            RoundButton { text: "3" }
            RoundButtonOperation { text: "+" }


            RoundButton { text: "0"; Layout.columnSpan: 2; Layout.fillWidth: true}
            RoundButton { text: "."
                MouseArea{
                    anchors.fill: parent
                    onClicked: calc.onPointButtonPressed();
                }
            }
            RoundButtonOperation {
                text: "="
                MouseArea{
                    anchors.fill: parent
                    onClicked: calc.onResultButtonPressed()
                }
            }

        }



    Item {
            id: keyCatcher
            anchors.fill: parent
            focus: true

            Keys.onPressed: (event) => {
                switch (event.key) {
                case Qt.Key_0: case Qt.Key_1: case Qt.Key_2:
                case Qt.Key_3: case Qt.Key_4: case Qt.Key_5:
                case Qt.Key_6: case Qt.Key_7: case Qt.Key_8:
                case Qt.Key_9:
                    calc.onNumberButtonPressed(event.text)
                    break;

                case Qt.Key_Plus:    calc.onOperationButtonPressed("+"); break;
                case Qt.Key_Minus:   calc.onOperationButtonPressed("-"); break;
                case Qt.Key_Slash:   calc.onOperationButtonPressed("/"); break;
                case Qt.Key_Asterisk:calc.onOperationButtonPressed("*"); break;
                case Qt.Key_Percent: calc.onOperationButtonPressed("%"); break;

                case Qt.Key_Return:
                case Qt.Key_Enter:  calc.onResultButtonPressed(); break;

                case Qt.Key_Backspace: calc.onBackspaceButtonPressed(); break;
                case Qt.Key_Delete:    calc.onClearButtonPressed(); break;

                case Qt.Key_Period:
                case Qt.Key_Comma: calc.onPointButtonPressed(); break;
                }
            }
        }

}

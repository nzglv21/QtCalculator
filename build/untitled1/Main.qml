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
        MouseArea{
            anchors.fill: parent
            onClicked: calc.onButtonPressed(button.text)
        }
    }

    component RoundButtonOperation: RoundButton{
        color: "#F1A33B"
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
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
            anchors.fill: parent
            anchors.margins: 4
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

            RoundButtonTool{text: "AC"}
            RoundButtonTool{text: "+/-"}
            RoundButtonTool{text: "%"}
            RoundButtonOperation { text: "÷" }


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
            RoundButton { text: "," }
            RoundButtonOperation { text: "=" }

        }



}

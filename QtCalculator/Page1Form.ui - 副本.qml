import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    width: 600
    height: 400
    property alias rectangle: rectangle

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10

        Grid {
            id: grid1
            x: 200
            y: 0
            width: 400
            height: 400
        }

        Label {
            id: rectangle
            x: 200
            y: 26
            width: 84
            height: 84
            color: "#b6afaf"
            text: "7"
        }

        Label {
            id: rectangle1
            x: 290
            y: 26
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle2
            x: 200
            y: 116
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle3
            x: 290
            y: 116
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle4
            x: 200
            y: 206
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle5
            x: 290
            y: 206
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle6
            x: 200
            y: 297
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle7
            x: 290
            y: 297
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle8
            x: 380
            y: 26
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle9
            x: 470
            y: 26
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle10
            x: 380
            y: 116
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle11
            x: 470
            y: 116
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle12
            x: 380
            y: 206
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle13
            x: 470
            y: 206
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle14
            x: 380
            y: 297
            width: 84
            height: 84
            color: "#b6afaf"
        }

        Label {
            id: rectangle15
            x: 470
            y: 297
            width: 84
            height: 84
            color: "#b6afaf"
        }
    }

    TextInput {
        id: textInput
        x: 30
        y: 17
        width: 94
        height: 31
        color: "#ffffff"
        text: "输入表达式..."
        font.pixelSize: 12
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.9}
}
##^##*/


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.2

Page {
    width: 1280
    height: 720

    header: Label {
        id: _base
        //        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 3
        padding: 10
        property int button_offset_x: 510
        property int button_offset_y: 20
        property int button_size: 100
        property int button_margin: 120

        Button {
            id: b_lparenthese
            x: _base.button_offset_x + 0 * _base.button_margin
            y: _base.button_offset_y + 4 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "("
            onClicked: {
                tt.text += "("
            }
        }

        Button {
            id: b_rparenthese
            x: _base.button_offset_x + 1 * _base.button_margin
            y: _base.button_offset_y + 4 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: ")"
            onClicked: {
                tt.text += ")"
            }
        }
        Button {
            id: b_mod
            x: _base.button_offset_x + 4 * _base.button_margin
            y: _base.button_offset_y + 2 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            font.pixelSize: Qt.application.font.pixelSize * 2
            text: "Mod"
            onClicked: {
                tt.text += "%"
            }
        }

        Button {
            id: b7
            x: _base.button_offset_x + 0 * _base.button_margin
            y: _base.button_offset_y + 0 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "7"
            onClicked: {
                tt.text += "7"
            }
        }

        Button {
            id: b8
            x: _base.button_offset_x + 1 * _base.button_margin
            y: _base.button_offset_y + 0 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "8"
            onClicked: {
                tt.text += "8"
            }
        }

        Button {
            id: b9
            x: _base.button_offset_x + 2 * _base.button_margin
            y: _base.button_offset_y + 0 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "9"
            onClicked: {
                tt.text += "9"
            }
        }

        Button {
            id: b4
            x: _base.button_offset_x + 0 * _base.button_margin
            y: _base.button_offset_y + 1 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "4"
            onClicked: {
                tt.text += "4"
            }
        }

        Button {
            id: b5
            x: _base.button_offset_x + 1 * _base.button_margin
            y: _base.button_offset_y + 1 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "5"
            onClicked: {
                tt.text += "5"
            }
        }

        Button {
            id: b6
            x: _base.button_offset_x + 2 * _base.button_margin
            y: _base.button_offset_y + 1 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "6"
            onClicked: {
                tt.text += "6"
            }
        }

        Button {
            id: b1
            x: _base.button_offset_x + 0 * _base.button_margin
            y: _base.button_offset_y + 2 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "1"
            onClicked: {
                tt.text += "1"
            }
        }
        Button {
            id: b2
            x: _base.button_offset_x + 1 * _base.button_margin
            y: _base.button_offset_y + 2 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "2"
            onClicked: {
                tt.text += "2"
            }
        }
        Button {
            id: b3
            x: _base.button_offset_x + 2 * _base.button_margin
            y: _base.button_offset_y + 2 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "3"
            onClicked: {
                tt.text += "3"
            }
        }
        Button {
            id: b_add
            x: _base.button_offset_x + 3 * _base.button_margin
            y: _base.button_offset_y + 0 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "+"
            onClicked: {
                tt.text += "+"
            }
        }
        Button {
            id: b_sub
            x: _base.button_offset_x + 3 * _base.button_margin
            y: _base.button_offset_y + 1 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "-"
            onClicked: {
                tt.text += "-"
            }
        }

        Button {
            id: b_mul
            x: _base.button_offset_x + 3 * _base.button_margin
            y: _base.button_offset_y + 2 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "*"
            onClicked: {
                tt.text += "*"
            }
        }

        Button {
            id: b_div
            x: _base.button_offset_x + 3 * _base.button_margin
            y: _base.button_offset_y + 3 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "/"
            onClicked: {
                tt.text += "/"
            }
        }

        Button {
            id: b_00
            x: _base.button_offset_x + 2 * _base.button_margin
            y: _base.button_offset_y + 3 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "00"
            onClicked: {
                tt.text += "00"
            }
        }

        Button {
            id: b_0
            x: _base.button_offset_x + 1 * _base.button_margin
            y: _base.button_offset_y + 3 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "0"
            onClicked: {
                tt.text += "0"
            }
        }

        Button {
            id: b_dot
            x: _base.button_offset_x + 0 * _base.button_margin
            y: _base.button_offset_y + 3 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "."
            onClicked: {
                tt.text += "."
            }
        }
        Button {
            id: b_equ
            x: _base.button_offset_x + 4 * _base.button_margin
            y: _base.button_offset_y + 3 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "="
            onClicked: {
                QI.handle_exp(tt.text)
            }
        }
        Button {
            id: b_del
            x: _base.button_offset_x + 4 * _base.button_margin
            y: _base.button_offset_y + 0 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "←"
            onClicked: {
                tt.text = tt.text.slice(0, -1)
            }
        }
        Button {
            id: b_clear
            x: _base.button_offset_x + 4 * _base.button_margin
            y: _base.button_offset_y + 1 * _base.button_margin
            width: _base.button_size
            height: _base.button_size
            text: "C"
            onClicked: {
                tt.text = ""
            }
        }
    }

    TextEdit {
        id: tt
        objectName: "input_window"
        x: 20
        y: -30
        width: 500
        height: 500
        font.pixelSize: Qt.application.font.pixelSize * 3
        color: "#ffffff"
        text: ""
        wrapMode: Text.WrapAnywhere
        Keys.enabled: true
        Keys.onPressed: {
            console.log(event.key)
            switch (event.key) {
            case 16777221:
                QI.handle_exp(tt.text)
                break
            case 16777220:
                QI.handle_exp(tt.text)
                break
            default:
                break
            }
        }
        function set_res(s) {
            console.log(s)
            text = s
        }
    }

    TextEdit {
        id: calc_result
        objectName: "calc_result"
        x: 20
        y: 300
        width: 500
        height: 500
        font.pixelSize: Qt.application.font.pixelSize * 1.5
        color: "#ffffff"
        text: "result will be showed here"
        wrapMode: Text.WrapAnywhere
        function warning(msg) {
            color = "#ff0000"
            text = msg
        }
        function set_res(a1, a2, a3) {
            console.log(a1)
            color = "#ffffff"
            text = '表达式二叉树：
前序：' + a2 + '

中序：' + a1 + '

后序：' + a3
        }
    }
}

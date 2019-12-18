import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
ApplicationWindow{
    objectName: "res_view"
    title: "统计结果展示"
    id: res_view
    width: 1280
    height: 800
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    font.pixelSize: 20


    property var jsonobj: ({})
    property var exp_path: ''

    function clear_r(){
        list_root.clear()
        jsonobj=({})
        list_root.append({name:"单词",ind:"计数"})
    }

    function append_list(na,ctr){
        jsonobj[na]=ctr
        list_root.append({name:na,ind:ctr.toString()})
    }

    function exp_json(){
        exp_path= ''
        var new_file_dialog=Qt.createQmlObject('
import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
FileDialog {
    id: fileDialog
    title: "Please choose a path"
    folder: shortcuts.home
    selectFolder: true
    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
        res_view.exp_path=fileDialog.fileUrl
        //console.log(res_view.jsonobj["to"])
        DATAMGR.exp_file(res_view.exp_path,JSON.stringify(res_view.jsonobj))
        fileDialog.destroy()
    }
    onRejected: {
        console.log("Canceled")
        fileDialog.destroy()
    }
    Component.onCompleted: visible = true
}

',res_view,"dynamicSnippet1")
    }

    menuBar: ToolBar{
        id: add_rules_menu
        RowLayout{
            width: parent.width
            ToolButton{
                icon.source: "file:///C:/Users/Irori/qtPro/QMLview/icons/application-export.png"//图标的绝对路径
                onClicked: {
                    exp_json()
                }
            }

            TextField {
                id: input_rule
                Layout.fillWidth: true
                text: "左上可导出"
            }
        }
    }

    ListView {

        id: listView

        width: parent.width
        height: parent.height
        delegate: Item {

            width: add_rules_menu.width
            height: 40
            Row {
                id: row1
                Text {

                    font.pixelSize: 20
                    width: add_rules_menu.width*0.7
                    text: '<font color="#ffffff">'+name+'</font>'
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    width: add_rules_menu.width*0.3
                    text: '<font color="#ffffff">'+ind+'</font>'
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 20

                }


            }
        }
        model: ListModel {
            id: list_root
        }
    }

}

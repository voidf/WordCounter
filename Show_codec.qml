import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
ApplicationWindow{
    objectName: "co_view"
    title: "设置编码"
    id: co_view
    width: 500
    height: 800
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    font.pixelSize: 20

    function append_list(na){
        list_root.append({name:na})
    }

    function clear_r(){
        list_root.clear()
    }


    ListView {

        id: listView

        width: parent.width
        height: parent.height
        delegate: Item {

            width: co_view.width
            height: 40
            Row {
                id: row1
                Text {

                    font.pixelSize: 20
                    width: co_view.width*0.7
                    text: '<font color="#ffffff">'+name+'</font>'
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
                Button {
                    property var iid:name
                    font.pixelSize: 16
                    width: co_view.width*0.1
                    text: qsTr("选择")
                    onClicked: {
                        DATAMGR.set_codec(this.iid)
                        root.show_codec_selection(this.iid)
                    }
                }


            }
        }
        model: ListModel {
            id: list_root
        }
    }

}

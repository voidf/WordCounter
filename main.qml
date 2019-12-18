import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    property var cre : Qt.createComponent("Create_rules.qml").createObject(root);
    property var res : Qt.createComponent("Show_res.qml").createObject(root);
    objectName: "root_view"
    title: "WordCounter 单词统计"
    visible: true
    id: root
    width: 500
    height: 800
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    function create_split_rules(){
        var new_split_rule=cre
        if(new_split_rule){}
        else{
            new_split_rule= Qt.createComponent("Create_rules.qml").createObject(root);
            cre=new_split_rule
        }
        new_split_rule.show()
        DATAMGR.init_rules()
    }

    function create_res(){
        if(!res)
            res=Qt.createComponent("Show_res.qml").createObject(root);
        res.show()
    }

    function create_file_dialog(){
        var new_file_dialog=Qt.createQmlObject('
import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
FileDialog {
    id: fileDialog
    title: "Please choose a file"
    folder: shortcuts.home
    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrl)
        DATAMGR._file_path=fileDialog.fileUrl
        fileDialog.destroy()
    }
    onRejected: {
        console.log("Canceled")
        fileurl=""
        fileDialog.destroy()
    }
    Component.onCompleted: visible = true
}

',root,"dynamicSnippet1")
    }




    function create_element(){
        var new_object = Qt.createQmlObject('
import QtQuick 2.9;
import QtQuick.Controls.Material 2.3;
import QtQuick.Layouts 1.3;
import QtQuick.Controls 2.5;
Pane {
    id: son_list
    width: 200;
    height: 800;
    Layout.fillHeight: true;
    Material.elevation: 6;
    NumberAnimation on opacity{
        from: 0
        to: 100
        duration: 1000
    }
    Button{
        icon.source: "file:///C:/Users/Irori/qtPro/QMLview/icons/close.png";
        onClicked:{
            son_list.destroy();
        }
    }

    Item{
        children:[
            Button{
                y:100;
                text: qsTr("选择文件");
                onClicked:{
                    root.create_file_dialog();
                }
            },
            Button{
                y:200;
                text: qsTr("待扩展项");
            }
        ]


    }


}

',root,"dynamicSnippet1");
    }

    menuBar: ToolBar{
        id: menu
        RowLayout{
            width: parent.width
            ToolButton{
                icon.source: "file:///C:/Users/Irori/qtPro/QMLview/icons/plus.png"//图标的绝对路径
                onClicked: {

                    root.create_element();

                }
            }

            Label {
                Layout.fillWidth: true
                text: "单词统计系统"
            }
        }
    }

    function non_file(){
        console.log("nf")
        split_pattern.text=qsTr("错误:未选择文件")
    }

    function non_rule(){
        split_pattern.text=qsTr("错误:没有分割规则")
    }

    TextField {
        id: split_pattern
        x: 256
        y: 136
        width: 204
        height: 46
        color: "#ffffff"
        text: qsTr("请先左上选择文件")
        visible: true
        font.family: "PingFang SC Medium"
        clip: false
        font.pixelSize: 20
    }

    Button{
        x: 360
        y: 213
        text: qsTr("设置规则")
        onClicked: {
            create_split_rules();
        }
    }

    Button{
        x: 360
        y: 283
        text: qsTr("开始统计")
        onClicked: {
            create_res()
            DATAMGR.count_files();
        }
    }

}

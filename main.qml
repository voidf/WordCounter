import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
ApplicationWindow {
    property var cre : Qt.createComponent("Create_rules.qml").createObject(root);
    property var res : Qt.createComponent("Show_res.qml").createObject(root);
    property var co: Qt.createComponent("Show_codec.qml").createObject(root);

    property var upp : 1
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

    function create_codec(){
        if(!co)
            co=Qt.createComponent("Show_codec.qml").createObject(root);
        co.show()
    }

    function ignore_Up(){
        upp^=1;
        if (upp){
            split_pattern.text="考虑大小写"
        }
        else{
            split_pattern.text="忽略大小写"
        }
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
        icon.source: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAgY0hSTQAAeiYAAICEAAD6AAAAgOgAAHUwAADqYAAAOpgAABdwnLpRPAAAAAZiS0dEAAAAAAAA+UO7fwAAAAlwSFlzAAAASAAAAEgARslrPgAAAPlJREFUaN7tmMsKwjAQRY9W/7B0oX8nFhf+oRV000AoVfqYaaZwD2QTyvSehDRDQQghhBD7oQJuwNWhdg08gLNn+Bb4AG9jiRro+tpPL4kUPo0OaAzqNln4NFoPgRp4DV60difylc9rXjwErCU2D28pUSy8hUTx8GskwoRfIhEu/ByJsOGnSIQPnxi7kLofcxYXoAtjOxF+5adKuIQ/OkkcZs6HYezAWvZOruz6EP/7VHp0sZuFz58JKTHnkgonseSGDSOxpj0oLmHR2xSTsGzMNpfw6Co3ldj9b5UKuGOz8kPynXgCJw8B+sItPq1A09d2Cy+EEEIIa74anQUUA9PgGgAAACV0RVh0ZGF0ZTpjcmVhdGUAMjAxOS0xMi0xNVQwODowNjozMyswMDowMNBEiLkAAAAldEVYdGRhdGU6bW9kaWZ5ADIwMTktMTItMTVUMDg6MDY6MzMrMDA6MDChGTAFAAAAKHRFWHRzdmc6YmFzZS11cmkAZmlsZTovLy90bXAvbWFnaWNrLUxoNjREMHRQeZnvpQAAAABJRU5ErkJggg";
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
                text: qsTr("大小写");
                onClicked:{
                    DATAMGR.ignore_upper();
                    root.ignore_Up();
                }
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
                icon.source: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAgY0hSTQAAeiYAAICEAAD6AAAAgOgAAHUwAADqYAAAOpgAABdwnLpRPAAAAAZiS0dEAAAAAAAA+UO7fwAAAAlwSFlzAAAASAAAAEgARslrPgAAAFxJREFUaN7t17ENwCAMRUGc/Xd26qSiMV9R7gbAPNGYtQCAnJo6uLv7MahqZNY1FXCKgDQBaQLSBKQJSNveT967zfjFNnenz7+AgDT/gTQBaQLSBKQJSBMAAPzZDdSjDDbVGnaeAAAAJXRFWHRkYXRlOmNyZWF0ZQAyMDE5LTEyLTE1VDAzOjUzOjQ5KzAwOjAwDkYGSwAAACV0RVh0ZGF0ZTptb2RpZnkAMjAxOS0xMi0xNVQwMzo1Mzo0OSswMDowMH8bvvcAAAAodEVYdHN2ZzpiYXNlLXVyaQBmaWxlOi8vL3RtcC9tYWdpY2steU9XTFhaeW6f5AdoAAAAAElFTkSuQmCC"//图标的绝对路径
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

    function show_codec_selection(sel){
        split_pattern.text=qsTr("编码设置为"+sel)
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
        //font.family: "PingFang SC Medium"
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
        text: qsTr("设置编码")
        onClicked: {
            create_codec()
            DATAMGR.show_codec_list()
        }
    }

    Button{
        x: 360
        y: 353
        text: qsTr("开始统计")
        onClicked: {
            create_res()
            DATAMGR.count_files();
        }
    }

}

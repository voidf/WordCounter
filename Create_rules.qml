import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
ApplicationWindow{
    objectName: "add_rules_view"
    title: "分割依据设置,注意若有子串包含关系,则以下标小者优先"
    id: add_rules_view
    width: 500
    height: 800
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    font.pixelSize: 20


    menuBar: ToolBar{
        id: add_rules_menu
        RowLayout{
            width: parent.width
            ToolButton{
                icon.source: "file:///C:/Users/Irori/qtPro/QMLview/icons/plus.png"//图标的绝对路径
                onClicked: {

                    add_rules_view.create_r();

                }
            }

            TextField {
                id: input_rule
                Layout.fillWidth: true
                text: "在此处输入单词分隔符"
            }
        }
    }

    function clear_r(){
        list_root.clear()
    }

    function init_r(na){

        switch (na){
        case "\n":
            list_root.append({name:"换行符"+na,ind:list_root.count})
            break
        case " ":
            list_root.append({name:"空格"+na,ind:list_root.count})
            break
        case "\t":
            list_root.append({name:"制表符"+na,ind:list_root.count})
            break
        case "\v":
            list_root.append({name:"垂直制表符"+na,ind:list_root.count})
            break
        case "\r":
            list_root.append({name:"回车符"+na,ind:list_root.count})
            break
        case "\f":
            list_root.append({name:"换页"+na,ind:list_root.count})
            break
        case "\0":
            list_root.append({name:"空字符"+na,ind:list_root.count})
            break
        default:
            list_root.append({name:na,ind:list_root.count})
        }

    }

    function create_r(){
        var na=input_rule.text
        DATAMGR.add_rule(na)
        switch (na){
        case "\n":
            list_root.append({name:"换行符"+na,ind:list_root.count})
            break
        case " ":
            list_root.append({name:"空格"+na,ind:list_root.count})
            break
        case "\t":
            list_root.append({name:"制表符"+na,ind:list_root.count})
            break
        case "\v":
            list_root.append({name:"垂直制表符"+na,ind:list_root.count})
            break
        case "\r":
            list_root.append({name:"回车符"+na,ind:list_root.count})
            break
        case "\f":
            list_root.append({name:"换页"+na,ind:list_root.count})
            break
        case "\0":
            list_root.append({name:"空字符"+na,ind:list_root.count})
            break
        default:
            list_root.append({name:na,ind:list_root.count})
        }
        maintain_r();
    }

    function maintain_r(){
        //DATAMGR.init_rules();
        for(var i = 0; i < list_root.count; i++)
            list_root.setProperty(i,"ind",i);
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
                    width: add_rules_menu.width*0.2
                    text: '<font color="#ffffff">'+ind+'</font>'
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {

                    font.pixelSize: 20
                    width: add_rules_menu.width*0.7
                    text: '<font color="#ffffff">'+name+'</font>'
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                Button{
                    property var iid:ind
                    font.pixelSize: 16
                    width: add_rules_menu.width*0.1
                    text: qsTr("删除")
                    onClicked: {
                        list_root.remove(this.iid,1)
                        DATAMGR.del_rule(this.iid)
                        maintain_r()
                    }
                }
            }
        }
        model: ListModel {
            id: list_root
        }
    }

}

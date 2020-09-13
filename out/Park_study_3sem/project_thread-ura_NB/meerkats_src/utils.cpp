#include "utils.h"

GdbInterface::GdbInterface() {
    gdbArguments << "-q"
                  << "/home/byeti/project/megazord/megazord/rat_lab"
                  << "--interpreter=mi";
    gdb.setProgram("gdb");
    gdb.setArguments(gdbArguments);

    connect(&gdb, &QProcess::started, this, &GdbInterface::onGDBConnected);
    connect(&gdb, &QProcess::readyRead, this, &GdbInterface::gdbReadyRead);
}


void GdbInterface::onGDBConnected() {
    magicBox(command = "");
    magicBox(command = "set print pretty on");
    magicBox(command = "-break-insert main");
    magicBox(command = "-exec-run");
//  programm prepearing
}

void GdbInterface::update() {
    QByteArray stp;
        stp = magicBox(command = "step");
        if(stp.indexOf("__libc_start_main") != -1)
            return;
        history += stp;
        getCurrentScope(stp);
        sizeOfarraysControl(stp);
        while(magicEssence.size() >= countFrames() && !magicEssence.isEmpty()) {
            magicEssence.pop_back();
        }
        parserInfolocal();
}

void GdbInterface::parserInfolocal() {
    QByteArray infoLocal = magicBox(command = "info local");
    if(infoLocal.indexOf("No locals.") != -1)
        return;
    if(infoLocal.indexOf("#") != -1)
        return;
    magicEssence.push_back(empty2);
    //history += infoLocal;
    int beg = 0, end = 0;

    while(infoLocal.indexOf("~", beg + 1) != -1) {
        beg = infoLocal.indexOf("~", beg + 1);
        end = infoLocal.indexOf("~", beg + 1);
        QByteArray line = readFromTo(infoLocal, beg, end);
        if(end != -1)
            switch(identification(line, 0)) {
            case -1:
                break;
            case -2:
                break;
            case -3:
                break;
            case -4:
                break;

            case 0:  //  usualQube
                parserUsualQube(getNameVar(line, 0));
                break;
            case 1:  //  static array
                parserStaticArray(getNameVar(line, 0));
                break;
            case 2:  //  poiter or dynamic array
                parserUsualQube(getNameVar(line, 0));
                if(sizesDynamicArrays.find(getNameVar(line, 0)) != sizesDynamicArrays.end())
                    parserDynamicArray(getNameVar(line, 0));
                break;
            case 3:  //  static char array
                parserStaticArray(getNameVar(line, 0));
                break;
            }
    }
    for(int i = 0; i < magicEssence.size(); i++)
        for(int j = 0; j < magicEssence[i].size(); j++)
            for(int k = 0; k < magicEssence[i][j].size(); k++)
                if(magicEssence[i][j][k].type.indexOf("*") != -1)
                    if(addressingTable.contains(magicEssence[i][j][k].content))
                        for(int s = 0; s < 3; s++)
                            magicEssence[i][j][k].pointTo[s] = addressingTable
                                    .find(magicEssence[i][j][k].content)
                                    .value()
                                    .coord[s];
}

void GdbInterface::parserUsualQube(QByteArray name) {
    Qube cube;
    cube.name = name;
    cube.scope = currentScope;
    cube.coord[0] = magicEssence.size() - 1;

    magicEssence[cube.coord[0]].push_back(empty1);
    cube.coord[1] = magicEssence[cube.coord[0]].size() - 1;

    cube.coord[2] = magicEssence[cube.coord[0]][cube.coord[1]].size() - 1 + 1;
    cube.addr = getAddrVar(cube.name);
    cube.type = getTypeVar(cube.name);
    cube.content = getContentVar(cube.name);

    if(addressingTable.contains(cube.name)) {
        QMap<QByteArray, Qube>::iterator iter = addressingTable.find(cube.name);
        addressingTable.erase(iter);
    }
    addressingTable.insert(cube.addr, cube);

    magicEssence[cube.coord[0]][cube.coord[1]].push_back(cube);
}

void GdbInterface::parserStaticArray(QByteArray name) {
    Qube cube;
    cube.type = getTypeVar(name);
    int beg = 0, end = 0;
    if(cube.type.indexOf("struct ", beg) != -1) {
        parserStruct(name);
        return;
    }
    beg = cube.type.indexOf("[", beg) + 1;
    end = cube.type.indexOf("]", beg) - 1;
    int lenght = readFromTo(cube.type, beg, end).toInt();

    magicEssence[magicEssence.size() - 1].push_back(empty1);
    for(int i = 0; i < lenght; i++) {
        cube.name = name;
        cube.name += "[";
        cube.name += QString::number(i);
        cube.name += "]";
        cube.scope = currentScope;
        cube.coord[0] = magicEssence.size() - 1;

        cube.coord[1] = magicEssence[cube.coord[0]].size() - 1;

        cube.coord[2] = magicEssence[cube.coord[0]][cube.coord[1]].size() - 1 + 1;
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);

        if(addressingTable.contains(cube.name)) {
            QMap<QByteArray, Qube>::iterator iter = addressingTable.find(cube.name);
            addressingTable.erase(iter);
        }
        addressingTable.insert(cube.addr, cube);

        magicEssence[cube.coord[0]][cube.coord[1]].push_back(cube);
    }
    if(cube.type.indexOf("[") != -1)
        for(int i = 0; i < lenght; i++) {
            QByteArray childName;
            childName = name;
            childName += "[";
            childName += QString::number(i);
            childName += "]";
            parserStaticArray(childName);
        }
}

void GdbInterface::parserDynamicArray(QByteArray name) {
    Qube cube;
    QByteArray nameForFind;
    if(name.lastIndexOf("[") != -1) {
        int beg = 0;
        int end = name.lastIndexOf("[") - 1;
        nameForFind = readFromTo(name, beg, end);
    } else {
        nameForFind = name;
    }
    if(sizesDynamicArrays.contains(nameForFind)){
        int lenght = sizesDynamicArrays.find(nameForFind).value();

        magicEssence[magicEssence.size() - 1].push_back(empty1);
        for(int i = 0; i < lenght; i++) {
            cube.name = name;
            cube.name += "[";
            cube.name += QString::number(i);
            cube.name += "]";
            cube.scope = currentScope;
            cube.coord[0] = magicEssence.size() - 1;

            cube.coord[1] = magicEssence[cube.coord[0]].size() - 1;

            cube.coord[2] = magicEssence[cube.coord[0]][cube.coord[1]].size() - 1 + 1;
            cube.addr = getAddrVar(cube.name);
            cube.type = getTypeVar(cube.name);
            cube.content = getContentVar(cube.name);

            if(addressingTable.contains(cube.name)) {
                QMap<QByteArray, Qube>::iterator iter = addressingTable.find(cube.name);
                addressingTable.erase(iter);
            }
            addressingTable.insert(cube.addr, cube);

            magicEssence[cube.coord[0]][cube.coord[1]].push_back(cube);
        }
        if(cube.type.indexOf("*") != -1)
            for(int i = 0; i < lenght; i++) {
                QByteArray childName;
                childName = name;
                childName += "[";
                childName += QString::number(i);
                childName += "]";
                parserDynamicArray(childName);
            }
    }
}

void GdbInterface::sizeOfarraysControl(QByteArray step) {
    int beg = step.indexOf("~", 0);
    int end = step.indexOf("\n", beg);
    if(beg != -1 && end != -1) {
        QByteArray line = readFromTo(step, beg, end);
        beg = 0;
        end = 0;

        if(line.indexOf(" new ", 0) != -1) {
            beg = line.indexOf(" ", beg);  //  get name of array
            while(readNSymbols(line, beg, 0).indexOf(" ") != -1)
                beg++;
            end = line.indexOf(" ", beg) - 1;
            QByteArray name = readFromTo(line, beg, end);

            beg = line.indexOf(" = new ");  //  get size of new array
            beg = line.indexOf("[", beg) + 1;
            end = line.indexOf("]", beg) - 1;
            QByteArray sizeNew = readFromTo(line, beg, end);
            QByteArray nameFind;

            if(name.indexOf("[") != -1) {
                int endFind = name.lastIndexOf("[") - 1;
                int begFind = 0;
                nameFind  = readFromTo(name, begFind, endFind);
                if(nameFind.indexOf("[") != -1) {  //  ololo[i][j]  -->  ololo[0][0] for possible to find size in sizesDynamicArrays
                    int begEdit = 0;
                    QByteArray nameBuff = readFromTo(nameFind, 0, nameFind.indexOf("[") - 1);  //  coustruct base name

                    while((begEdit = nameFind.indexOf("[", begEdit + 1)) != -1) {  //  filling brackets
                        nameBuff += "[";
                        nameBuff += QString::number(0);
                        nameBuff += "]";
                    }
                    nameFind = nameBuff;
                }

                if(sizesDynamicArrays.contains(nameFind)){
                    QMap<QByteArray, int>::const_iterator iter = sizesDynamicArrays.find(nameFind);
                    int sizeOfArray = iter.value();

                    int begEdit = 0;
                    QByteArray nameBuff = readFromTo(nameFind, 0, nameFind.indexOf("[") - 1);  //  coustruct base name
                    while((begEdit = nameFind.indexOf("[", begEdit + 1)) != -1) {  //  filling brackets
                        nameBuff += "[";
                        nameBuff += QString::number(0);
                        nameBuff += "]";
                    }
                    nameFind = nameBuff;

                    for(int i = 0; i < sizeOfArray; i++) {
                        QByteArray pushName = readFromTo(name, 0, name.lastIndexOf("[") - 1);
                        pushName += "[";
                        pushName += QString::number(i);
                        pushName += "]";

                        if(addressingTable.contains(pushName)) {
                            QMap<QByteArray, int>::iterator iter = sizesDynamicArrays.find(pushName);
                            sizesDynamicArrays.erase(iter);
                        }
                        sizesDynamicArrays.insert(pushName, sizeNew.toInt());
                    }
                }

            } else {
                QString convertor;
                QByteArray pushName = name;

                sizesDynamicArrays.insert(pushName, sizeNew.toInt());
            }
        }
    }
}








void GdbInterface::parserMass(QByteArray massName, int currRow) {
    QVector<Qube> thirdDemention;
    Qube cube;
    int length = readFromTo(cube.type,
                            cube.type.indexOf("[") + 1,
                            cube.type.indexOf("]") -1).toInt();

    for(int i = 0; i < length; i++) {
        cube.scope = currentScope;
        cube.coord[0] = countFrames();
        cube.coord[1] = currRow;
        cube.coord[2] = i;
        cube.name = massName;
        cube.name += "[";
        cube.name += QString::number(i);
        cube.name += "]";
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);

        addressingTable.insert(cube.addr, cube);
        thirdDemention.push_back(cube);
    }
}

void GdbInterface::parserStruct(QByteArray name) {
    Qube cube;
    QByteArray structure = magicBox(command = "p " + name);
    int beg = 0, end = 0;


    beg = structure.indexOf("{", beg) + 1;
    while(structure.indexOf(" = ", beg) != -1) {
        end = structure.indexOf(" = ", beg) - 1;

        while((structure.indexOf(" ", beg) + 1) < end) {
            beg = structure.indexOf(" ", beg) + 1;
        }
        cube.name = name;
        cube.name += ".";
        cube.name += readFromTo(structure, beg, end);

        cube.scope = currentScope;
        cube.coord[0] = magicEssence.size() - 1;

        cube.coord[1] = magicEssence[cube.coord[0]].size() - 1;

        cube.coord[2] = magicEssence[cube.coord[0]][cube.coord[1]].size() - 1 + 1;

        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);

        cube.content = getContentVar(cube.name);

        magicEssence[cube.coord[0]][cube.coord[1]].push_back(cube);
        if(addressingTable.contains(cube.name)) {
            QMap<QByteArray, Qube>::iterator iter = addressingTable.find(cube.name);
            addressingTable.erase(iter);
        }
        addressingTable.insert(cube.addr, cube);

        if(readNSymbols(structure, end, 4).indexOf("{") != -1) {
            end = structure.indexOf("}", end);
            end = structure.indexOf(" = ", end) - 1;
        }
    }
    for(int i = 0; i < magicEssence[magicEssence.size()]
        [magicEssence[magicEssence.size()].size()]
        .size(); i++) {
        Qube cube = magicEssence[magicEssence.size()]
                [magicEssence[magicEssence.size()].size()]
                [i];
        if(cube.type.indexOf("struct ") != -1)
            parserStruct(cube.name);
    }
}

void GdbInterface::magicFirst() {

    while(magicEssence.size() >= countFrames()) {
        magicEssence.pop_back();
    }
}

void GdbInterface::magicSecond(QByteArray infoLocal) {
    Qube cube;
    QVector<Qube> thirdDemention;
    QVector<QVector<Qube>> secondDemention;
    int beg = 0, end = 0;

    while((beg = infoLocal.indexOf("~", beg + 1)) != -1) {
        switch(identification(infoLocal, beg)) {
        case -1:
            break;
        case -2:
            break;
        case -3:
            break;
        case -4:
            break;
        default:
            end = infoLocal.indexOf("~", beg + 1);
            QByteArray line = readFromTo(infoLocal, beg, end);

            //push_back
            break;
        }

    }
}

void GdbInterface::parserQube(QByteArray lineWithName, int sizeOY) {
    QVector<Qube> thirdDemention;
    QMap<QByteArray, Qube>::const_iterator find;
    Qube cube;
    int beg = 0;

    switch(identification(lineWithName, beg)) {
    case 0:
        cube.scope = currentScope;
        cube.name = getNameVar(lineWithName, beg);
        cube.coord[0] = countFrames();
        cube.coord[1] = sizeOY;
        cube.coord[2] = 0;
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);

        addressingTable.insert(cube.addr, cube);
        thirdDemention.push_back(cube);
        break;
    case 1:
        cube.scope = currentScope;
        cube.name = getNameVar(lineWithName, beg);
        cube.coord[0] = countFrames();
        cube.coord[1] = sizeOY;
        cube.coord[2] = 0;
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);

        if(cube.type.indexOf("[") != -1){  //  Silver for massives...
            parserMass(cube.name, sizeOY);
        }
        if(cube.type.indexOf("struct") != -1) {  //  ... steel for structers.
            parserStruct(cube.name);
        }
        break;
    case 2:
        cube.scope = currentScope;
        cube.name = getNameVar(lineWithName, beg);
        cube.coord[0] = countFrames();
        cube.coord[1] = sizeOY;
        cube.coord[2] = 0;
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);


        find = addressingTable.find(cube.addr);
        for(int i = 0; i < 3; i++)
            cube.pointTo[i] = find.value().coord[i];


        addressingTable.insert(cube.addr, cube);
        thirdDemention.push_back(cube);
        break;
    case 3:
        cube.scope = currentScope;
        cube.name = getNameVar(lineWithName, beg);
        cube.coord[0] = countFrames();
        cube.coord[1] = sizeOY;
        cube.coord[2] = 0;
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);

        parserMass(cube.name, sizeOY);
        break;
    default:
        cube.scope = currentScope;
        cube.name = getNameVar(lineWithName, beg);
        cube.coord[0] = countFrames();
        cube.coord[1] = sizeOY;
        cube.coord[2] = 0;
        cube.addr = getAddrVar(cube.name);
        cube.type = getTypeVar(cube.name);
        cube.content = getContentVar(cube.name);

        addressingTable.insert(cube.addr, cube);
        thirdDemention.push_back(cube);
        break;
    }
}

QByteArray GdbInterface::readFromTo(QByteArray stroke, int beg, int end){  //  ok
    QByteArray readed;
    for(int i = beg; i <= end; i++)
            readed += stroke[i];
    return readed;
}

QByteArray GdbInterface::readNSymbols(QByteArray stroke, int beg, int symbols) {  //  ok
    return readFromTo(stroke, beg, beg + symbols);  //  if word 6 chars, symbols = 5
}

QByteArray GdbInterface::getNameVar(QByteArray commandResult, int  tildaIndex) {  //  ok
    int beg = tildaIndex + 2;
    int end = commandResult.indexOf(" = ", beg) - 1;
    return readFromTo(commandResult, beg, end);
}

QByteArray GdbInterface::getTypeVar(QByteArray name) {  //  ok
    QByteArray type = magicBox(command = ("ptype " + name));
    int beg = 0, end = 0;

    beg = type.indexOf("~", 0) ;
    beg = type.indexOf(" ", beg) + 3;
    end = type.indexOf("\\n", beg) - 1;
    if (type.indexOf("{", beg) != -1)
        end = type.indexOf("{", beg) - 2;

    return readFromTo(type, beg, end);
}

QByteArray GdbInterface::getAddrVar(QByteArray name) {  //  ok
    QByteArray addr = magicBox(command = ("p &" + name));
    int beg = 0, end = 0;

    beg = addr.indexOf("0x", 0);
    end = addr.indexOf("\n", beg) - 2;
    if(addr.indexOf(" ", beg) < addr.indexOf("\n", beg))
        end = addr.indexOf(" ", beg) - 1;

    return readFromTo(addr, beg, end);
}

QByteArray GdbInterface::getContentVar(QByteArray name) {  //  ok
    QByteArray content = magicBox(command = (("p " + name)) + " ");
    int beg = 0, end = 0;

    beg = content.indexOf(" = ", beg) + 3;
    end = content.indexOf("\n", beg) - 2;

    if(readFromTo(content, end - 2, end).indexOf(">") != -1)
        end = content.indexOf("<", beg) - 1;
    if(content.indexOf("0x", beg) != -1)
        beg = content.indexOf("0x", beg);
    if(content.indexOf("\\\\", beg) < end && content.indexOf("\\\\", beg) != -1) {
        beg = content.indexOf("\\\\", beg) + 2;
        end = content.indexOf("\'", beg) - 1;
    } else {
        if(content.indexOf("\'", beg) < end && content.indexOf("\'", beg) != -1) {
            beg = content.indexOf("\'", beg) + 1;
            end --;
        }
    }
    if(content.indexOf(" ", beg) < end && content.indexOf(" ", beg) != -1)
        end = content.indexOf(" ", beg) - 1;

    return readFromTo(content, beg, end);
}

void GdbInterface::getCurrentScope(QByteArray step) {  //  ok
    int beg = 0, end = 0;

    beg = step.indexOf("*", beg);
    if(step.indexOf(",func=", beg) != -1)
        beg = step.indexOf(",func=", beg);
    else {
     currentScope = "(No scope)";
     return;
    }
    beg = step.indexOf("\"", beg) + 1;
    end = step.indexOf("\"", beg) - 1;
    currentScope = readFromTo(step, beg, end);
}

int GdbInterface::countVars(QByteArray commandResult) {  // ok
    QByteArray local = commandResult;
    int count = 0;
    int beg = 0;

    beg = local.indexOf("~", 0);
    beg = local.indexOf(" ", beg) + 3;  //  on first char content

    while(beg != -1) {
        if(readNSymbols(local, beg, 3).indexOf("\\n", 0) != -1) {
            beg = local.indexOf("~", beg + 1);
        } else {
            if(readNSymbols(local, local.indexOf(" ", beg) + 3, 0).indexOf("{", 0) != -1) {
                beg = local.indexOf("}", beg);
                beg = local.indexOf("~", beg);
                count ++;
            } else {
                beg = local.indexOf("~", beg + 1);
                count++;
            }
        }
    }
    return count;
}

int GdbInterface::countFrames() {  //  ok
    QByteArray btrace = magicBox(command = "bt");
    int count = 0;
    int beg = 0;

    while((beg = btrace.indexOf("~", beg + 1)) != -1)
        count++;

    return count;
}

QByteArray GdbInterface::magicBox(QByteArray unprocessedCommand) {  //  ok
    if(!unprocessedCommand.isEmpty())
        unprocessedCommand += "\n";

    gdb.write(unprocessedCommand);
    gdb.waitForReadyRead(-1);
    QByteArray processedCommand;
    processedCommand = mainClipboard;
    mainClipboard.clear();

    return processedCommand;
}

void GdbInterface::gdbReadyRead() {
    QByteArray readed;
    bool final = false;
    while(!final) {
        gdb.waitForFinished(1);
        readed = gdb.readAll();
        mainClipboard += readed;

        if(readed.indexOf("-exec-run") != -1) {
            gdb.waitForFinished(1);
            readed = gdb.readAll();
            mainClipboard += readed;
        }
        if(readed.indexOf("&\"step\n\"") != -1) {
            gdb.waitForFinished(1);
            readed = gdb.readAll();
            mainClipboard += readed;
        }
        if(readed.indexOf("(gdb)") != -1)
            final = true;
    }
}

int GdbInterface::identification(QByteArray commandResult,
                                int varIndex){  //  varIndex - index of "~" before ur var
    int type = 0;
    QByteArray check;


    if((check = readNSymbols(commandResult, varIndex, 3)).indexOf("\\n") != -1)
        return -1;
    if((check = readNSymbols(commandResult, varIndex, 2)).indexOf(",") != -1)
        return -2;
    if((check = readNSymbols(commandResult, varIndex, 2)).indexOf(" ") != -1)
        return -3;
    if((check = readNSymbols(commandResult, varIndex, 2)).indexOf("}") != -1)
        return -4;

    varIndex = commandResult.indexOf(" = ", varIndex) + 3;  //  on first character word

    if((check = readNSymbols(commandResult, varIndex, 0)).indexOf("{", 0) != -1) {  //  static massive or srtuct
        type = 1;
    }
    if((check = readNSymbols(commandResult, varIndex, 1)).indexOf("0x", 0) != -1) {  //  pointer
        type = 2;
    }
    if((check = readNSymbols(commandResult, varIndex, 0)).indexOf("\\", 0) != -1) {  //  char[] massive or string
        type = 3;
    }
    if((check = readNSymbols(commandResult, varIndex, 0)).indexOf("<", 0) != -1) {  //  not init or error
        type = 4;
    }
    //Dynamic
    return type;
}


QByteArray GdbInterface::getFrameName(QByteArray lvl) {
    QByteArray trace = magicBox(command = "bt");
    QByteArray find = "#";
    find += lvl;
    int beg = 0, end = 0;
    beg = trace.indexOf(find, 0) + 1;
    end = trace.indexOf(" ", beg);
    return readFromTo(trace, beg, end);
}

let socket = new WebSocket("ws://localhost:9002");

// maps thread ids to their thread name
const threadMap = new Map();

/**
 * Update the gui with the data from the payload
 * @param threadInfo JSON object containing the thread info
 */
updateGui = function (threadInfo) {
    if (threadInfo.modules.length === 0) {
        document.getElementById("ModuleTable").style.visibility = "hidden";
        document.getElementById("ThreadInfoTable").style.visibility = "hidden"
    } else {
        // update module table
        let moduleTable = document.getElementById("ModuleTable");
        moduleTable.style.visibility = "visible"
        let newModuleTbody = document.createElement('tbody');
        // sort modules by module name
        let sortedModules = threadInfo.modules.sort((a, b) => a.name.localeCompare(b.name));
        sortedModules.forEach(module => {
            let newRow = document.createElement("tr");

            let nameCell = document.createElement("td");
            let sum_rtCell = document.createElement("td");
            let max_rtCell = document.createElement("td");
            let avg_rtCell = document.createElement("td");
            let sum_vsCell = document.createElement("td");
            let sum_isCell = document.createElement("td");
            // jsonObject.dump() does not keep "order" in the json string for nlohmann/json!
            for(const [moduleKey, moduleValue] of Object.entries(module)){
                if(moduleKey === "name"){
                    nameCell.innerText = moduleValue;
                } else if (moduleKey === "sum_rt"){
                    sum_rtCell.innerText = moduleValue;
                } else if (moduleKey === "max_rt"){
                    max_rtCell.innerText = moduleValue;
                } else if (moduleKey === "avg_rt"){
                    avg_rtCell.innerText = moduleValue;
                } else if (moduleKey === "sum_vs"){
                    sum_vsCell.innerText = moduleValue;
                } else if (moduleKey === "sum_is"){
                    sum_isCell.innerText = moduleValue;
                }
            }
            newRow.appendChild(nameCell);
            newRow.appendChild(sum_rtCell);
            newRow.appendChild(max_rtCell);
            newRow.appendChild(avg_rtCell);
            newRow.appendChild(sum_vsCell);
            newRow.appendChild(sum_isCell);
            newModuleTbody.appendChild(newRow);
        });
        let oldModuleTbody = moduleTable.childNodes[1].getElementsByTagName('tbody')[0];
        oldModuleTbody.parentNode.replaceChild(newModuleTbody, oldModuleTbody);

        //update thread info table
        let threadInfoTable = document.getElementById("ThreadInfoTable");
        threadInfoTable.style.visibility = "visible"
        let newThreadInfoTbody = document.createElement('tbody');
        let newRow = document.createElement("tr");
        ["tid", "freq", "iterations", "overruns", "sum_rt"].forEach(s => {
            let cell = document.createElement("td");
            cell.innerText = threadInfo[s];
            newRow.appendChild(cell);
        });
        newThreadInfoTbody.appendChild(newRow);
        let oldThreadInfoTbody = threadInfoTable.childNodes[1].getElementsByTagName('tbody')[0];
        oldThreadInfoTbody.parentNode.replaceChild(newThreadInfoTbody, oldThreadInfoTbody);
    }
    //update graph
    document.getElementById('graph_svg').innerHTML = threadInfo.graphSvg;
    // get width of graph svg and set it as width of the svg element
    let bBox = document.getElementById('graph_svg').getBBox();
    document.getElementById('graph_svg').style.width = bBox.width;
}

/**
 * Update the options in the thread dropdowns from the thread map
 */
updateDropdown = function () {
    let lhsDropdown = document.getElementById("lhsThread");
    let rhsDropdown = document.getElementById("rhsThread");
    while (lhsDropdown.options.length > 1) { // keep first element ("select a thread")
        lhsDropdown.remove(1);
    }
    while (rhsDropdown.options.length > 1) {
        rhsDropdown.remove(1);
    }
    // sort the map by thread name
    let sortedThreadMap = new Map([...threadMap.entries()].sort((a, b) => a[1].localeCompare(b[1])));

    // set the key of each thread as the (internal) value of the option and use the thread name as the display text
    sortedThreadMap.forEach((value, key) => {
        let option1 = document.createElement("option");
        option1.value = key;
        option1.text = value;
        lhsDropdown.appendChild(option1);
        let option2 = document.createElement("option");
        option2.value = key;
        option2.text = value;
        rhsDropdown.appendChild(option2);
    })
}

/**
 * Handles the selection of a thread in the dropdown
 */
threadSelected = function () {
    let leftDropdown = document.getElementById("lhsThread");
    let selected = leftDropdown.options[leftDropdown.selectedIndex];
    let message = {
        "sender": "gui",
        "topic": "requestData",
        "payload": {
            "tid": selected.value
        }
    }
    socket.send(JSON.stringify(message));
}

/**
 * Handles incoming messages from the server
 * add or update thread data in the threadMap
 * @param event
 */
socket.onmessage = function (event) {
    let message = JSON.parse(event.data);
    if (message.sender === "server") {
        switch (message.topic) {
            case "startup":
                message.payload.forEach(thread => {
                    threadMap.set(thread.tid, thread.name);
                });
                updateDropdown();
                document.getElementById("submit").addEventListener("click",submitOperation);
                break;
            case "provideData":
                updateGui(message.payload);
        }
    }
}

submitOperation = function() {
    let lhs = document.getElementById("lhsThread").options[document.getElementById("lhsThread").selectedIndex].value;
    let rhs = document.getElementById("rhsThread").options[document.getElementById("rhsThread").selectedIndex].value;
    let operation = document.getElementById("operation").options[document.getElementById("operation").selectedIndex].value;
    let resultingGraphName = document.getElementById("threadName").value;

    if(lhs === "" || rhs === "" || operation === "" || resultingGraphName === ""){
        alert("Please fill out all fields");
        return false;
    }

    if(Array.from(threadMap.values()).includes(resultingGraphName)){
        alert("Entered thread name already exists");
        return false;
    }

    let message = {
        "sender": "gui",
        "topic": "operation",
        "payload": {
            "lhs": lhs,
            "operation": operation,
            "rhs": rhs,
            "resultingGraphName": resultingGraphName
        }
    }
    threadMap.set(resultingGraphName, resultingGraphName);
    // send operation to server
    socket.send(JSON.stringify(message));
    updateDropdown();

    // automatically select and request data for the new thread
    document.getElementById("lhsThread").value = resultingGraphName;
    document.getElementById("rhsThread").value = "";
    document.getElementById("operation").value = "";
    document.getElementById("threadName").value = "";
    socket.send(JSON.stringify({
        "sender": "gui",
        "topic": "requestData",
        "payload": {
            "tid": resultingGraphName
        }
    }));
    return false;
}

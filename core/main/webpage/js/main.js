let socket = new WebSocket("ws://localhost:9002");

// maps thread ids to their thread name
const threadMap = new Map();

let testPayload = {
    "tid": "1234",
    "name": "tollerthread",
    "freq": 62.5,
    "iterations": 1,
    "overruns": 100,
    "sum_rt": 98134719,
    "modules": [{
        "name": "toles module",
        "sum_rt": 1,
        "max_rt": 2,
        "avg_rt": 3,
        "sum_vs": 4,
        "sum_is": 5
    },
        {
            "name": "tolles module",
            "sum_rt": 11,
            "max_rt": 22,
            "avg_rt": 33,
            "sum_vs": 43,
            "sum_is": 5
        },
        {
            "name": "tollles module",
            "sum_rt": 1,
            "max_rt": 2,
            "avg_rt": 3,
            "sum_vs": 4,
            "sum_is": 5
        }
    ],
    "graphPath": "img\\graph_placeholder.svg"
}

let composedPayload = {
    "tid": "1234",
    "modules": [],
    "graphPath": "img\\graph_placeholder.svg"
}

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
        threadInfo.modules.forEach(module => {
            let newRow = document.createElement("tr");
            Object.values(module).forEach((moduleValue) => {
                let cell = document.createElement("td");
                cell.innerText = moduleValue;
                newRow.appendChild(cell);
            })
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
    document.getElementById("graph_svg").src = threadInfo.graphPath;
}

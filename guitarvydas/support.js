exports.panic = function () {
    console.error ('macro unrecognized');
    //throw "panic";
}

var param1stack = [];
var param2stack = [];
var param3stack = [];

exports.pushParam1 = function (s) { param1stack.push (s); return ''; }
exports.pushParam2 = function (s) { param2stack.push (s); return ''; }
exports.pushParam3 = function (s) { param3stack.push (s); return ''; }

exports.getParam1 = function () { 
    var topx = param1stack.length - 1;
    return param1stack [topx];
}
exports.getParam2 = function () { 
    var topx = param2stack.length - 1;
    return param2stack [topx];
}
exports.getParam3 = function () { 
    var topx = param3stack.length - 1;
    return param3stack [topx];
}

exports.popParams = function () {
    param1stack.pop ();
    param2stack.pop ();
    param3stack.pop ();
}


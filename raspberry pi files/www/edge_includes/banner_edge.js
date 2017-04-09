/**
 * Adobe Edge: symbol definitions
 */
(function($, Edge, compId){
//images folder
var im='images/';

var fonts = {};
var opts = {};
var resources = [
];
var symbols = {
"stage": {
    version: "3.0.0",
    minimumCompatibleVersion: "3.0.0",
    build: "3.0.0.322",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
            {
                id: 'banner',
                type: 'image',
                rect: ['0', '0','900px','381px','auto', 'auto'],
                fill: ["rgba(0,0,0,0)",im+"banner.png",'0px','0px']
            },
            {
                id: 'banner1',
                type: 'image',
                rect: ['0', '0','900px','381px','auto', 'auto'],
                opacity: 0,
                fill: ["rgba(0,0,0,0)",im+"banner1.png",'0px','0px']
            }],
            symbolInstances: [

            ]
        },
    states: {
        "Base State": {
            "${_Stage}": [
                ["color", "background-color", 'rgba(255,255,255,1)'],
                ["style", "width", '900px'],
                ["style", "height", '381px'],
                ["style", "overflow", 'hidden']
            ],
            "${_banner}": [
                ["style", "opacity", '1']
            ],
            "${_banner1}": [
                ["style", "opacity", '0.000000']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 9000,
            autoPlay: true,
            labels: {
                "loop": 0
            },
            timeline: [
                { id: "eid1", tween: [ "style", "${_banner}", "opacity", '1', { fromValue: '1'}], position: 0, duration: 0 },
                { id: "eid3", tween: [ "style", "${_banner}", "opacity", '0', { fromValue: '1'}], position: 4000, duration: 250 },
                { id: "eid9", tween: [ "style", "${_banner}", "opacity", '1', { fromValue: '0.000000'}], position: 8750, duration: 250 },
                { id: "eid5", tween: [ "style", "${_banner1}", "opacity", '1', { fromValue: '0.000000'}], position: 4250, duration: 250 },
                { id: "eid7", tween: [ "style", "${_banner1}", "opacity", '0', { fromValue: '1'}], position: 8500, duration: 250 }            ]
        }
    }
}
};


Edge.registerCompositionDefn(compId, symbols, fonts, resources, opts);

/**
 * Adobe Edge DOM Ready Event Handler
 */
$(window).ready(function() {
     Edge.launchComposition(compId);
});
})(jQuery, AdobeEdge, "EDGE-87532410");

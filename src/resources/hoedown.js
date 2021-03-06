var placeholder = document.getElementById('placeholder');

// Use Marked to highlight code blocks.
marked.setOptions({
    highlight: function(code) {
        return hljs.highlightAuto(code).value;
    }
});

var updateHtml = function(html) {
    placeholder.innerHTML = html;
    var codes = document.getElementsByTagName('code');
    mermaidIdx = 0;
    for (var i = 0; i < codes.length; ++i) {
        var code = codes[i];
        if (code.parentElement.tagName.toLowerCase() == 'pre') {
            if (VEnableMermaid && code.classList.contains('language-mermaid')) {
                // Mermaid code block.
                mermaidParserErr = false;
                mermaidIdx++;
                try {
                    // Do not increment mermaidIdx here.
                    var graph = mermaidAPI.render('mermaid-diagram-' + mermaidIdx, code.innerText, function(){});
                } catch (err) {
                    content.setLog("err: " + err);
                    continue;
                }
                if (mermaidParserErr || typeof graph == "undefined") {
                    continue;
                }
                var graphDiv = document.createElement('div');
                graphDiv.classList.add(VMermaidDivClass);
                graphDiv.innerHTML = graph;
                var preNode = code.parentNode;
                preNode.classList.add(VMermaidDivClass);
                preNode.replaceChild(graphDiv, code);
                // replaceChild() will decrease codes.length.
                --i;
            } else {
                hljs.highlightBlock(code);
            }
        }
    }

    // MathJax may be not loaded for now.
    if (VEnableMathjax && (typeof MathJax != "undefined")) {
        try {
            MathJax.Hub.Queue(["Typeset", MathJax.Hub, placeholder]);
        } catch (err) {
            content.setLog("err: " + err);
        }
    }
};

var highlightText = function(text, id, timeStamp) {
    var html = marked(text);
    content.highlightTextCB(html, id, timeStamp);
}


$(function() {
    var $tempfield = $('#tempfield');
    var $hygfield = $('#hygfield');

    function refresh() {
        // make Ajax call here, inside the callback call:
        console.log("getting request");
        
        $.getJSON("http://192.168.5.130/api/sensors", function (data, status) {
            console.log(status + ' ' + data);
            $tempfield.text(data.temperature);
            $hygfield.text(data.humidity);
        });

        setTimeout(refresh, 5000);
    }

    // initial call, or just call refresh directly
    refresh();
});

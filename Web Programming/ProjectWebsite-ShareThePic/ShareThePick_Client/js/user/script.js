$(document).ready(function(){
    $(document).foundation();
    var $window = $(window);
    var $leftColumn = $('#leftColumn');
    var top = $leftColumn.offset().top - 45;
    var left = $leftColumn.offset().left;
    //console.log(top);
    //console.log($('#rightColumn').offset().top);
    var width = $leftColumn.css('width');
    //console.log(width);
    //console.log($(window).width());
    if ($(window).width() > 1024) {
        $(document).on('scroll', function(){
            var scrollTop = $window.scrollTop();
            if (scrollTop >= top) {
                //console.log($leftColumn.hasClass('fixed'));
                if (!$leftColumn.hasClass('fixed')) {
                    $leftColumn.css({
                        left: left,
                        width: width
                    });
                    $leftColumn.addClass('fixed');
                }
            } else {
                if ($leftColumn.hasClass('fixed')) {
                    $leftColumn.removeClass('fixed');
                    $leftColumn.css({
                        left:0
                    });
                }
            }
        });
    }

});
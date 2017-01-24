/**
 * Created by Show on 4/23/15.
 */

$(document).ready(function () {
    $(document).foundation({
        orbit: {
            next_on_click: false, // Advance to next slide on click
            slide_number: false,
            slide_number_text: 'of',
            bullets: true, // Does the slider have bullets visible?
            circular: false, // Does the slider should go to the first slide after showing the last?
            timer: false, // Does the slider have a timer active? Setting to false disables the timer.
            variable_height: false, // Does the slider have variable height content?
            swipe: true
        }
    });
    $(window).trigger('resize');
    $(document).keydown(function(e){
        if (e.keyCode == 18) {
            $('.deleteIcon').show();
        }
    });
    $(document).keyup(function(e){
        if (e.keyCode == 18) {
            $('.deleteIcon').hide();
        }
    });
});
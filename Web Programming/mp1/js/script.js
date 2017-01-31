/*
var divs = document.getElementsByTagName('div');
for(var i=0; i<divs.length; i++) {
  divs[i].addEventListener("click", highlightThis);
  
 // divs[i].addEventListener("click", highlightThis, true);
 // divs[i].addEventListener("click", highlightThis, false);
}

function highlightThis(event) {
    //event.stopPropagation();
  
    var backgroundColor = this.style.backgroundColor;
    this.style.backgroundColor='yellow';
    alert(this.className);
    this.style.backgroundColor=backgroundColor;
}
*/



(function($){$.fn.extend({leanModal:function(options){var defaults={top:100,overlay:0.5,closeButton:null};var overlay=$("<div id='lean_overlay'></div>");$("body").append(overlay);options=$.extend(defaults,options);return this.each(function(){var o=options;$(this).click(function(e){var modal_id=$(this).attr("href");$("#lean_overlay").click(function(){close_modal(modal_id)});$(o.closeButton).click(function(){close_modal(modal_id)});var modal_height=$(modal_id).outerHeight();var modal_width=$(modal_id).outerWidth();
$("#lean_overlay").css({"display":"block",opacity:0});$("#lean_overlay").fadeTo(200,o.overlay);$(modal_id).css({"display":"block","position":"fixed","opacity":0,"z-index":11000,"left":50+"%","margin-left":-(modal_width/2)+"px","top":o.top+"px"});$(modal_id).fadeTo(200,1);e.preventDefault()})});function close_modal(modal_id){$("#lean_overlay").fadeOut(200);$(modal_id).css({"display":"none"})}}})})(jQuery);


$(document).ready(function(){
	$("#carousel_ul li:first").before($("#carousel_ul li:last"));

	$("#right_arrow img").click(function(){
		var item_width= $("#carousel_ul li").outerWidth();
		var left_indent= parseInt($("#carousel_ul").css("left"))-item_width;

		$("#carousel_ul").animate({"left": left_indent},500,function(){
			$("#carousel_ul li:last").after($("#carousel_ul li:first"));
			$("#carousel_ul").css({"left":"-320px"});
		});
	
	});

	$("#left_arrow img").click(function(){
		var item_width=$("#carousel_ul li").outerWidth();
		var left_indent=parseInt($("#carousel_ul").css("left"))+ item_width;

		$("#carousel_ul").animate({"left": left_indent},500,function(){
			$("#carousel_ul li:first").before($("#carousel_ul li:last"));
			$("#carousel_ul").css({"left":"-320px"});
		});
	});
});


$(document).on("scroll",function(){
	if($(document).scrollTop()>100){
		$("header").removeClass("large").addClass("small");
	} else{
		$("header").removeClass("small").addClass("large");
	}
});


$(function() {
  $('a[href*=#]:not([href=#])').click(function() {
    if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'') && location.hostname == this.hostname) {
      var target = $(this.hash);
      target = target.length ? target : $('[name=' + this.hash.slice(1) +']');
      if (target.length) {
        $('html,body').animate({
          scrollTop: target.offset().top
        }, 1000);
        return false;
      }
    }
  });
});


$(document).on("scroll",function(){
	if(($(document).scrollTop())>10 && $(document).scrollTop()<500){
		$("#self_introduction_navi").addClass("highlight");
	} else {
		$("#self_introduction_navi").removeClass("highlight");
	}
	if($(document).scrollTop()>500&& $(document).scrollTop()<900){
		$("#self_photo_navi").addClass("highlight");
	} else {
		$("#self_photo_navi").removeClass("highlight");
	}
	if(($(document).scrollTop())>900 && $(document).scrollTop()<1200){
		$("#friends_photo_navi").addClass("highlight");
	} else {
		$("#friends_photo_navi").removeClass("highlight");
	}
	if(($(document).scrollTop())>1200){
		$("#video_navi").addClass("highlight");
	} else {
		$("#video_navi").removeClass("highlight");
	}

});


function Modal_qingdao_func() {
/*	el = document.getElementById("overlay");
	el.style.visibility = (el.style.visibility == "visible") ? "hidden" : "visible";
	el = document.getElementById("Qingdao_modal");
	el.style.visibility = (el.style.visibility == "visible") ? "hidden" : "visible";
	el = document.getElementById("Close_qingdao");
	el.style.visibility = (el.style.visibility == "visible") ? "hidden" : "visible";*/
$("#Click_qingdao").leanModal();


}



    $(document).ready(function() {
        //Show modal box
        $('#openModal').click(
            function() {$('.dumbBoxWrap').show();}
        );
        //Hide modal box
        $('#closeModal').click(
            function() {$('.dumbBoxWrap').hide();}
        );
    });




/*
References:
http://www.webdesignerdepot.com/2013/03/how-to-create-a-resizing-menu-bar/
*/



/*
 @licstart  The following is the entire license notice for the
 JavaScript code in this file.

 Copyright (C) 1997-2017 by Dimitri van Heesch

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 @licend  The above is the entire license notice
 for the JavaScript code in this file
 */
function initResizable()
{
  var cookie_namespace = 'doxygen';
  var sidenav,navtree,content,header,showButton,collapsed,barWidth=6,desktop_vp=768;

  function readCookie(cookie)
  {
    var myCookie = cookie_namespace+"_"+cookie+"=";
    if (document.cookie) {
      var index = document.cookie.indexOf(myCookie);
      if (index != -1) {
        var valStart = index + myCookie.length;
        var valEnd = document.cookie.indexOf(";", valStart);
        if (valEnd == -1) {
          valEnd = document.cookie.length;
        }
        var val = document.cookie.substring(valStart, valEnd);
        return val;
      }
    }
    return 0;
  }

  function writeCookie(cookie, val, expiration)
  {
    if (val==undefined) return;
    if (expiration == null) {
      var date = new Date();
      date.setTime(date.getTime()+(10*365*24*60*60*1000)); // default expiration is one week
      expiration = date.toGMTString();
    }
    document.cookie = cookie_namespace + "_" + cookie + "=" + val + "; expires=" + expiration+"; path=/";
  }

  function resizeWidth()
  {
    var sidenavWidth = $(sidenav).outerWidth();
    content.css({marginLeft:parseInt(sidenavWidth)+"px"});
    writeCookie('width',sidenavWidth-barWidth, null);
  }

  function restoreWidth(navWidth)
  {
    content.css({marginLeft:parseInt(navWidth)+barWidth+"px"});
    sidenav.css({width:navWidth + "px"});
  }

  function toggleCollapsed() {
    collapsed = !collapsed;
    if (collapsed) {
      sidenav.removeClass('shown');
      sidenav.addClass('hidden');
      showButton.text('Show menu');
    } else {
      sidenav.addClass('shown');
      sidenav.removeClass('hidden');
      showButton.text('Hide menu');
    }
  }

  function onResize() {
    var width=$(window).width();
    if (width < desktop_vp) {
      $(".collapsible").css({"display": ""});
      collapsed = !collapsed;
      toggleCollapsed();
      $(".headertitle").css({"padding-top": "0.5rem"});
      $(".ui-resizable-handle").css({display: "none"});
      sidenav.css({"max-width": "none", position: "initial", width: "auto", "padding": "0 1rem 1rem 1rem"});
      content.css({marginLeft: "0px", height: "", "overflow-y": ""});
    } else {
      $(".collapsible").css({"display": "none"});
      sidenav.removeClass('shown');
      sidenav.removeClass('hidden');
      $(".ui-resizable-handle").css({display: ''});
      $(".headertitle").css({"padding-top": ""});
      sidenav.css({"max-width": "", position: "", width: "", "padding": ""});
      content.css({"overflow-y": "auto", height: "100%"});

      var width = readCookie('width');
      if (width) { restoreWidth(width); } else { resizeWidth(); }
    }
  }

  header  = $("#top");
  sidenav = $("#side-nav");
  content = $("#doc-content");
  navtree = $("#nav-tree");
  footer  = $("#nav-path");
  showButton = $("#show-menu-button");

  $(".side-nav-resizable").resizable({resize: function(e, ui) { resizeWidth(); } });
  $(sidenav).resizable({ minWidth: 250 });
  $(window).resize(function(event) {
    if (event.target === window) {
      onResize();
    }
  });

  showButton.click(toggleCollapsed);

  $('.ui-resizable-e').css({ width: '4px' });
  barWidth=20;

  onResize();

  var url = location.href;
  var i=url.indexOf("#");
  if (i>=0) window.location.hash=url.substr(i);
  var _preventDefault = function(evt) { evt.preventDefault(); };
  $("#splitbar").bind("dragstart", _preventDefault).bind("selectstart", _preventDefault);
  }
/* @license-end */

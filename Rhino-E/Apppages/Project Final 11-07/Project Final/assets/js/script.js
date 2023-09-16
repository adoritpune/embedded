$(function(){
	
	var colors = [
		'26e000','2fe300','37e700','45ea00','51ef00',
		'61f800','6bfb00','77ff02','80ff05','8cff09',
		'93ff0b','9eff09','a9ff07','c2ff03','d7ff07',
		'f2ff0a','fff30a','ffdc09','ffce0a','ffc30a',
		'ffb509','ffa808','ff9908','ff8607','ff7005',
		'ff5f04','ff4f03','f83a00','ee2b00','e52000'
	];
	
	var rad2deg = 180/Math.PI;
	var deg = 0;
	var bars = $('#bars');
    var bars1 = $('#bars1');	
	var bars2 = $('#bars2');
	
	for(var i=0;i<colors.length;i++){
		
		deg = i*12;
		
		// Create the colorbars
		
		$('<div class="colorBar">').css({
			backgroundColor: '#'+colors[i],
			transform:'rotate('+deg+'deg)',
			top: -Math.sin(deg/rad2deg)*60+100,
			left: Math.cos((180 - deg)/rad2deg)*60+100,
		}).appendTo(bars);
		
		
		
		$('<div class="colorBar1">').css({
			backgroundColor: '#'+colors[i],
			transform:'rotate('+deg+'deg)',
			top: -Math.sin(deg/rad2deg)*60+100,
			left: Math.cos((180 - deg)/rad2deg)*60+100,
		}).appendTo(bars1);
		
		$('<div class="colorBar2">').css({
			backgroundColor: '#'+colors[i],
			transform:'rotate('+deg+'deg)',
			top: -Math.sin(deg/rad2deg)*60+100,
			left: Math.cos((180 - deg)/rad2deg)*60+100,
		}).appendTo(bars2);
		
		
		
	}
	
	var colorBars = bars.find('.colorBar');
	var colorBars1 = bars1.find('.colorBar1');
	var colorBars2 = bars2.find('.colorBar2');
	var numBars = 0, lastNum = -1;
	var numBarsValue=0;
	$('#control').knobKnob({
		snap : 10,
		value: 5,
		turn : function(ratio){
			numBars = Math.round(colorBars.length*ratio);
			numBarsValue=Math.round(colorBars.length*ratio);
			numBarsValue=numBarsValue*14;
			if(numBarsValue <= 10){
			  numBarsValue=10;
			}	
            if(numBarsValue>=400)
            {
				numBarsValue=400;
            } 
            document.getElementById("SetCurrent").innerHTML = numBarsValue;			
			console.log(numBarsValue);
			// Update the dom only when the number of active bars
			// changes, instead of on every move
			
			if(numBars == lastNum){
				return false;
			}
			lastNum = numBars;
			
			colorBars.removeClass('active').slice(0, numBars).addClass('active');
		}
	});
	
	
	
	$('#control1').knobKnob({
		snap : 10,
		value: 0,
		turn : function(ratio){
			numBars = Math.round(colorBars1.length*ratio);
			console.log(numBars*3.33);
			// Update the dom only when the number of active bars
			// changes, instead of on every move
			
			if(numBars == lastNum){
				return false;
			}
			lastNum = numBars;
			
			colorBars1.removeClass('active').slice(0, numBars).addClass('active');
		}
	});
	
	
	$('#control2').knobKnob({
		snap : 10,
		value: 0,
		turn : function(ratio){
			numBars = Math.round(colorBars2.length*ratio);
			console.log(numBars*3.33);
			// Update the dom only when the number of active bars
			// changes, instead of on every move
			
			if(numBars == lastNum){
				return false;
			}
			lastNum = numBars;
			
			colorBars2.removeClass('active').slice(0, numBars).addClass('active');
		}
	});
	
});

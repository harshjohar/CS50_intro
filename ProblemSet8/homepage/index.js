function greet()
{
    let name = document.querySelector('#name').value;
    if (name === '')
    {
        name = 'world';
    }
    alert("hello," + name + '!');
    document.querySelector('#result').innerHTML = 'hello, ' + name + '!';
}

function blink()
{
    let body = document.querySelector('div');

    if(body.style.visibility === 'hidden')
    {
        body.style.visibility = 'visible';
    }
    else
    {
        body.style.visibility = 'hidden';
    }
}

//blink evry 500 ms
window.setInterval(blink, 250);
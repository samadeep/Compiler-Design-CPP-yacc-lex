import fetch from 'node-fetch';

async function asteroidOrbits(year, orbitclass) 
{
    let arr=[];
    
    const fun = async (str1,str2)=>
    {
        let n=1;

        

        for (let i=0;i <n;i+=1)
        {
           let result = await fetch('https://jsonmock.hackerrank.com/api/asteroid?&pages =${i+1}')
           result = await  result.json();
            let pageData = result.data;
            for (let i in pageData)
            {
                let data = pageData[i]
                let year =  data.discovery_date.substr(0,4).toString()
                let orbitData = data.orbit_class.toString()
                if(year===str1 && orbitData=== str2)
                    {
                        arr.push(data)
                    }    
                }

                n = result.total_pages;        }
        }

        arr = arr.sort(a,b)=>{
            if(a.period_yr > b.period_yr)
            {
              return 1;  
            }
            else {
                return -1;
            }
             
        }
        else {
            return -1;
        }
    }};
    
    let resultArr =[];
    for (let i in arr )
    {
        resultArr.push(arr[i].designation)
    }
console.log(resultArr)
}
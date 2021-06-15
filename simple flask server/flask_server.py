from flask import Flask, render_template
import datetime

app = Flask(__name__)

@app.route('/soilstatushandler', methods=['POST'])
def soilstatushandler():
    soilvar1 = request.data # Got the data here.. the rest is optional!
    date = datetime.datetime.now()
    fDate = (date.strftime("%Y.%m.%d-%H:%M"))
    latestSoilUpdate1 = fDate + " " + soilvar1

    with open("/path_to_file/soilLog.txt", "a") as appendsoil:
         appendsoil.write(latestSoilUpdate1 + "\n")

    with open("/path_to_file/soilFile.txt", "r") as readsoil:
         oldfile = [line.strip() for line in readsoil]
         newfile = oldfile[-9:]
         newfile.append(latestSoilUpdate1)

    with open("/path_to_file/soilFile.txt", "a") as writesoil:
         writesoil.truncate(0)

         for i in range(10):
             writesoil.write(newfile[i] + "\n")

    return '''SoilData: {} --- {}.'''.format(fDate, soilvar1)

@app.route('/', methods=['GET'])
def soilstatus():
    with open("/path_to_file/soilFile.txt", "r") as readsoil:
        soilstatus = []
        soilstatuslist = [line.strip() for line in readsoil]

        try:
            for i in range(len(soilstatuslist)-1, -1, -1):
                soilstatus.append(soilstatuslist[i])

        except:
            readsoil.close()

    return render_template('soilstatus.html', soilstatus=soilstatus)

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0')

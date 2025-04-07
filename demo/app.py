from flask import Flask, request, jsonify, render_template
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/test')
def test():
    return render_template('test.html')

@app.route('/compute', methods=['POST'])
def compute():
    try:
        m1 = request.form.get('m1')
        m2 = request.form.get('m2')
        m3 = request.form.get('m3')

        if not all([m1, m2, m3]):
            return 'All three values are required!', 400

        # Call the binary with m1 m2 m3
        result = subprocess.check_output(['/home/vartikatrao/Desktop/LHSS/build/demo/sample', m1, m2, m3], stderr=subprocess.STDOUT)
        result_text = result.decode('utf-8')

    except subprocess.CalledProcessError as e:
        result_text = f"Error: {e.output.decode('utf-8')}"

    return f"<h2>Result</h2><pre>{result_text}</pre><a href='/'>Back</a>"

if __name__ == '__main__':
    app.run(debug=True)

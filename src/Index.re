// Turning off HMR for this until I can prevent re-appending root
// set isHotEnabled equal to module.hot
// [@bs.val] [@bs.scope "module"] external isHotEnabled: bool = "hot";
// set hotAccept equal to module.hot.accept
// [@bs.val] [@bs.scope ("module", "hot")]
// external hotAccept: unit => unit = "accept";

[@bs.val] external document: Js.t({..}) = "document";
type point = array(float);
type labelledPoint = {
  point: point,
  actual: int
};
type generator = {
  weights: array(float),
  points: array(point)
};
let nn = () => {
  let x_max: float = 400.;
  let y_max: float = 400.;
  let rand = (min, max) => Random.float(1.) *. (max -. min) +. min;
  let generator = () => {
    // Js.log(rand(2., 3.));
    // Js.log(1.->Random.float);
    let points = (length) =>
      Array.init(length, (_) => [|rand(0., x_max), rand(0., y_max)|]);
    let weights = [|rand(-1., 1.), rand(-1., 1.)|];
    let team = (point) => (point[0] > point[1] ? 1 : 0);
    let labeller = (points) =>
      Array.map((point) => ({ point, actual: team(point) }), points);
    let examples = (length) => labeller(points(length));
    ( weights, points, examples );
  };
  let chart = (height, width) => {
    let element = (name) =>
      document##createElementNS("http://www.w3.org/2000/svg", name);

    let svg = () => {
      let elem = element("svg");
      let () = elem##setAttribute("height", height);
      let () = elem##setAttribute("width", width);
      ();
    };
    let circle = (point: point, r: float, fill: string) => {
      let [|cx, cy|] = point;
      let elem = element("circle");
      let () = elem##setAttribute("cx", cx);
      let () = elem##setAttribute("cy", cy);
      let () = elem##setAttribute("r", r);
      let () = elem##setAttribute("fill", fill);
      ();
    };
    let line = (point1: point, point2: point, stroke: string) => {
      let [|x1, y1|] = point1;
      let [|x2, y2|] = point2;
      let elem = element("line");
      let () = elem##setAttribute("x1", x1);
      let () = elem##setAttribute("y1", y1);
      let () = elem##setAttribute("x2", x2);
      let () = elem##setAttribute("y2", y2);
      let () = elem##setAttribute("stroke", stroke);
      ();
    };
    ( circle, line, svg );
  };

  let draw = () => {
    let drawPointLabel = (point) => {
      // ignore non-exhaustive warning
      // @link https://2ality.com/2018/01/lists-arrays-reasonml.html#pattern-matching-and-arrays
      let [|x, y|] = Array.map(Js.Float.toString, point);
      // @link https://rescript-lang.org/docs/manual/v8.0.0/overview#string--character
      {j|($(x), $(y))|j}
    }
    let drawP = (parent, text) => {
      let elem = document##createElement("p");
      elem##innerText #= text;
      let () = parent##appendChild(elem);
      ();
    };

    let root = document##createElement("div");
    root##id #= "root";
    drawP(root, drawPointLabel([|rand(-1., 1.), rand(-1., 1.)|]));
    let () = document##body##appendChild(root);
    ();
  };
  draw();
};

nn();

// Turned off HMR because it keeps re-appending root
// there's probably some hot.dispose function that I can write
// enable HMR
/* if (isHotEnabled) { */
/*   hotAccept(); */
/* }; */

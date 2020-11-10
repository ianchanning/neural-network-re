// Turning off HMR for this until I can prevent re-appending root
// set isHotEnabled equal to module.hot
// [@bs.val] [@bs.scope "module"] external isHotEnabled: bool = "hot";
// set hotAccept equal to module.hot.accept
// [@bs.val] [@bs.scope ("module", "hot")]
// external hotAccept: unit => unit = "accept";

[@bs.val] external document: Js.t({..}) = "document";
type point = {
  point: array(float),
  actual: int
};
type generator = {
  weights: array(float),
  points: array(array(float))
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
  let draw = () => {
    let drawPointLabel = (point) =>
      "(" ++ Js.Float.toString(point[0]) ++ ","
        ++ Js.Float.toString(point[1]) ++ ")"
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

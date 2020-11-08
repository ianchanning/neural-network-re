// Turning off HMR for this until I can prevent re-appending root
// set isHotEnabled equal to module.hot
// [@bs.val] [@bs.scope "module"] external isHotEnabled: bool = "hot";
// set hotAccept equal to module.hot.accept
// [@bs.val] [@bs.scope ("module", "hot")]
// external hotAccept: unit => unit = "accept";

[@bs.val] external document: Js.t({..}) = "document";
let nn = () => {
  let rand = (min, max) => Random.float(1.) *. (max -. min) +. min;
  Js.log(rand(2., 3.));
  Js.log(1.->Random.float);
  let draw = () => {
    let drawP = (parent, text) => {
      let elem = document##createElement("p");
      elem##innerText #= text;
      let () = parent##appendChild(elem);
      ();
    };

    let root = document##createElement("div");
    root##id #= "root";
    drawP(root, "(0,0)");
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

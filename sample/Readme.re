let component = ReasonReact.statelessComponent("Readme");
let make = children => {
  ...component,
  render: _self =>
    <div>
      <a href="http://lol.to" title="shit">
        (ReasonReact.string({|link|}))
      </a>
    </div>,
};
